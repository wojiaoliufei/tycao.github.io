#include "cfivegoai.h"
using namespace FiveGo;

CFiveGoAI::CFiveGoAI()
{
    srand(time(nullptr));
}

void CFiveGoAI::GetStoneList(TStoneInfoList& stones) const
{
    for (int y = 0; y < c_boardSize; ++y)
        for (int x = 0; x < c_boardSize; ++x)
        {
            if ('*' == m_boardInfo.m_board[y][x])
                stones.push_back(TStoneInfo(x + 1, y + 1, true));
            else if ('o' == m_boardInfo.m_board[y][x])
                stones.push_back(TStoneInfo(x + 1, y + 1, false));
        }
}

TMoveInfo CFiveGoAI::StartGame(bool AiIsBlack, int AiDept)
{
    m_IsStart = true;
    m_AiIsBlack = AiIsBlack;
    m_CurrentIsAi = false;
    m_AiDept = AiDept;
    memset(m_boardInfo.m_board, '+', c_boardSize * c_boardSize);
    m_boardInfo.m_moveInfo = TMoveInfo();
    m_boardInfo.m_maxX = m_boardInfo.m_maxY = m_boardInfo.m_minX = m_boardInfo.m_minY = 0;
    if (m_AiIsBlack)
    {
        m_boardInfo.m_moveInfo.m_isBlack = true;
        m_boardInfo.m_moveInfo.m_x = m_boardInfo.m_moveInfo.m_y = 8;
        this->SetBoardState(m_boardInfo);
    }
    return m_boardInfo.m_moveInfo;
}

TMoveInfo CFiveGoAI::PlayerMove(int x, int y)
{
    TMoveInfo mi;
    mi.m_x = x;
    mi.m_y = y;
    mi.m_isBlack = !m_AiIsBlack;
    if (m_IsStart && TMoveInfo::EmiIsWin != m_boardInfo.m_moveInfo.m_moveState && !m_CurrentIsAi && CheckMove(m_boardInfo, x, y,  mi.m_isBlack))
    {
        for (int i = max(0, x - 2); i < min(c_boardSize - 1, x + 1); ++i)
            for (int j = max(0, y - 2); j < min(c_boardSize - 1, y + 1); ++j)
                if (m_AiIsBlack) m_value[j][i] += rand() % 7 + 1; else m_value[j][i] -= rand() % 7 + 1;
        m_boardInfo.m_moveInfo = mi;
        this->SetBoardState(m_boardInfo);
        m_CurrentIsAi = true;
        return m_boardInfo.m_moveInfo;
    }
    else return mi;
}

TMoveInfo CFiveGoAI::AIMove(void)
{
    TMoveInfo mi;
    mi.m_isBlack = m_AiIsBlack;
    if (m_IsStart && TMoveInfo::EmiIsWin != m_boardInfo.m_moveInfo.m_moveState && m_CurrentIsAi)
    {
        mi = this->AI(m_boardInfo, m_AiDept);
        mi.m_searchTime = m_boardInfo.m_moveInfo.m_searchTime;
        m_boardInfo.m_moveInfo = mi;
        this->SetBoardState(m_boardInfo);
        m_CurrentIsAi = false;
    }
    return mi;
}

inline void CFiveGoAI::SetBoardState(TBoardInfo& bi)
{
    bi.m_board[bi.m_moveInfo.m_y - 1][bi.m_moveInfo.m_x - 1] = (bi.m_moveInfo.m_isBlack ? '*' : 'o');
    if (bi.m_moveInfo.m_x > bi.m_maxX || 0 == bi.m_maxX) bi.m_maxX = bi.m_moveInfo.m_x;
    if (bi.m_moveInfo.m_x < bi.m_minX || 0 == bi.m_minX) bi.m_minX = bi.m_moveInfo.m_x;
    if (bi.m_moveInfo.m_y > bi.m_maxY || 0 == bi.m_maxY) bi.m_maxY = bi.m_moveInfo.m_y;
    if (bi.m_moveInfo.m_y < bi.m_minY || 0 == bi.m_minY) bi.m_minY = bi.m_moveInfo.m_y;
    bi.m_moveInfo.m_moveState = CheckWin(bi, bi.m_moveInfo.m_x, bi.m_moveInfo.m_y, bi.m_moveInfo.m_isBlack) ? TMoveInfo::EmiIsWin : TMoveInfo::EmiValid;
}

inline bool CFiveGoAI::CheckMove(const TBoardInfo& bi, int x, int y, bool)
{
    return bi.m_board[y - 1][x - 1] == '+';
}

inline bool CFiveGoAI::CheckWin(const TBoardInfo& bi, int x, int y, bool IsBlack)
{
    auto Exists = [=](int x, int y)
    {
        return bi.m_board[y - 1][x - 1] == (IsBlack ? '*' : 'o');
    };
    // 遍历4个方向
    int sum = 1;
    for (int i = 1; i < 5 && Exists(x + i, y); ++i) ++sum;
    for (int i = 1; i < 5 && Exists(x - i, y); ++i) ++sum;
    if (sum >= 5) return true;
    sum = 1;
    for (int i = 1; i < 5 && Exists(x, y + i); ++i) ++sum;
    for (int i = 1; i < 5 && Exists(x, y - i); ++i) ++sum;
    if (sum >= 5) return true;
    sum = 1;
    for (int i = 1; i < 5 && Exists(x + i, y + i); ++i) ++sum;
    for (int i = 1; i < 5 && Exists(x - i, y - i); ++i) ++sum;
    if (sum >= 5) return true;
    sum = 1;
    for (int i = 1; i < 5 && Exists(x - i, y + i); ++i) ++sum;
    for (int i = 1; i < 5 && Exists(x + i, y - i); ++i) ++sum;
    if (sum >= 5) return true;
    return false;
}

inline TMoveInfo CFiveGoAI::AI(const TBoardInfo& bi, int dept)
{
    m_boardInfo.m_moveInfo.m_searchTime = 0;
    return MaxMin(bi, dept, m_AiIsBlack, TMoveInfo());
}

// 评分算法
inline int CFiveGoAI::Score(const TBoardInfo& bi)
{
    int iSum = 0;
    // 按4个方向，取下一个位置和上一个位置
    auto FGetNextPosX = [=](int& x, int&) { return ++x; };
    auto FGetLastPosX = [=](int& x, int&) { return --x; };
    auto FGetNextPosY = [=](int&, int& y) { return ++y; };
    auto FGetLastPosY = [=](int&, int& y) { return --y; };
    auto FGetNextPosXY = [=](int& x, int& y) { return ++x, ++y; };
    auto FGetLastPosXY = [=](int& x, int& y) { return --x, --y; };
    auto FGetNextPosYX = [=](int& x, int& y) { return --x, ++y; };
    auto FGetLastPosYX = [=](int& x, int& y) { return ++x, --y; };
    // 在某位置，遍历所有图形，累加得分
    auto FSumPos = [&](int x, int y, function<char(int&, int&)> next, function<char(int&, int&)> last) -> int
    {
        int iStep = 1;
        // 判断图形是否存在
        auto FCheckUnit = [&](const TScoreUnit& su, int sLen) -> bool
        {
            // 在棋盘上，取位置上的字符
            auto FGetChar = [&](int ix, int iy) -> char
            {
                return (ix <= 15 && ix > 0 && iy <= 15 && iy > 0) ? bi.m_board[iy - 1][ix - 1] : 0;
            };
            // 循环每个字符
            bool bExists = true;
            int ix = x, iy = y;
            for (int j = 0; j < sLen && bExists; ++j, next(ix, iy))
                if (FGetChar(ix, iy) != su.m_info[j]) bExists = false;
            // 检查后面空位
            if (bExists)
                for (int j = 0; j < su.m_bp && bExists; ++j, next(ix, iy))
                    if (FGetChar(ix, iy) != '+') bExists = false;
            // 检查前面空位
            if (bExists)
            {
                ix = x, iy = y;
                last(ix, iy);
                for (int j = 0; j < su.m_fp && bExists; ++j, last(ix, iy))
                    if (FGetChar(ix, iy) != '+') bExists = false;
            }
            // 累积加分
            if (bExists)
            {
                iSum += su.m_score;
                iStep = sLen + su.m_bp;
            }
            return bExists;
        };
        // 从大到小，按图形循环
        for (int i = sizeof(c_ScoreList) / sizeof(TScoreUnit) - 1; i >= 0; --i)
        {
            const TScoreUnit& su = c_ScoreList[i];
            int sLen = strlen(su.m_info);
            // 正向查找
            if (FCheckUnit(su, sLen)) break;
            // 反向查找
            if (!su.m_swap)
            {
                char sInfo[20] = {0};
                for (int i = 0; i < sLen; ++i) sInfo[i] = *(su.m_info + sLen - i - 1);
                TScoreUnit suf(sInfo, su.m_fp, su.m_bp, su.m_swap, su.m_score);
                if (FCheckUnit(suf, sLen)) break;
            }
        }
        return iStep;
    };
    // 遍历棋子：水平 -
    for (int y = bi.m_minY; y <= bi.m_maxY; ++y)
        for (int x = bi.m_minX, step = 1; x <= bi.m_maxX; x += step, step = 1)
            if ('+' != bi.m_board[y - 1][x - 1])
                step = FSumPos(x, y, FGetNextPosX, FGetLastPosX);
    // 遍历棋子：垂直 |
    for (int x = bi.m_minX; x <= bi.m_maxX; ++x)
        for (int y = bi.m_minY, step = 1; y <= bi.m_maxY; y += step, step = 1)
            if ('+' != bi.m_board[y - 1][x - 1])
                step = FSumPos(x, y, FGetNextPosY, FGetLastPosY);
    // 遍历棋子：正对角线 \.
    for (int xy = bi.m_minX; xy <= bi.m_maxX; ++xy)
        for (int x = xy, y = bi.m_minY, step = 1; y <= bi.m_maxY && x <= bi.m_maxX; y += step, x += step, step = 1)
            if ('+' != bi.m_board[y - 1][x - 1])
                step = FSumPos(x, y, FGetNextPosXY, FGetLastPosXY);
    for (int yx = bi.m_minY + 1; yx <= bi.m_maxY; ++yx)
        for (int x = bi.m_minX, y = yx, step = 1; y <= bi.m_maxY && x <= bi.m_maxX; y += step, x += step, step = 1)
            if ('+' != bi.m_board[y - 1][x - 1])
                step = FSumPos(x, y, FGetNextPosXY, FGetLastPosXY);
    // 遍历棋子：反对角线 /
    for (int xy = bi.m_maxX; xy >= bi.m_minX; --xy)
        for (int x = xy, y = bi.m_minY, step = 1; y <= bi.m_maxY && x >= bi.m_minX; y += step, x -= step, step = 1)
            if ('+' != bi.m_board[y - 1][x - 1])
                step = FSumPos(x, y, FGetNextPosYX, FGetLastPosYX);
    for (int yx = bi.m_minY + 1; yx <= bi.m_maxY; ++yx)
        for (int x = bi.m_maxX, y = yx, step = 1; y <= bi.m_maxY && x >= bi.m_minX; y += step, x -= step, step = 1)
            if ('+' != bi.m_board[y - 1][x - 1])
                step = FSumPos(x, y, FGetNextPosYX, FGetLastPosYX);
    return iSum;
}

// 极大极小值搜索算法
inline TMoveInfo CFiveGoAI::MaxMin(const TBoardInfo& bi, int dept, bool IsBlack, TMoveInfo uncle)
{
    TMoveInfo mi;
    // 得到循环序列
    struct TPosXY
    {
        bool operator()(int i, int j) { return m_IsBlack ? i > j : i < j; }
        int x = 0, y = 0;
        bool m_IsBlack = true;
        TPosXY(int ix = 0, int iy = 0) : x(ix), y(iy) {}
        TPosXY(bool IsBlack) : m_IsBlack(IsBlack) {}
    } _comp(IsBlack);
    multimap<int, TPosXY, TPosXY> yxList(_comp);
    for (int x = max(1, bi.m_minX - 2), mx = min(c_boardSize, bi.m_maxX + 2); x <= mx; ++x)
        for (int y = max(1, bi.m_minY - 2), my = min(c_boardSize, bi.m_maxY + 2); y <= my; ++y)
            if (this->CheckMove(bi, x, y, IsBlack))
                yxList.insert(make_pair(m_value[y - 1][x - 1], TPosXY(x, y)));
    // 循环每个有效位置
    for (auto it = yxList.begin(); yxList.end() != it; ++it, ++m_boardInfo.m_moveInfo.m_searchTime)
    {
        // 创建盘面分支
        TBoardInfo biSub = bi;
        biSub.m_moveInfo.m_y = it->second.y;
        biSub.m_moveInfo.m_x = it->second.x;
        biSub.m_moveInfo.m_isBlack = IsBlack;
        this->SetBoardState(biSub);

        // 获胜，直接得满分
        if (TMoveInfo::EmiIsWin == biSub.m_moveInfo.m_moveState)
            biSub.m_moveInfo.m_score = biSub.m_moveInfo.m_isBlack ? c_fullScore : -c_fullScore;
        // 到最底层，进行评分算法
        if (1 >= dept)
            biSub.m_moveInfo.m_score = this->Score(biSub);
        // 递归搜索下层得分
        else
            biSub.m_moveInfo.m_score = this->MaxMin(biSub, dept - 1, !IsBlack, mi).m_score;
        m_value[biSub.m_moveInfo.m_y - 1][biSub.m_moveInfo.m_x - 1] = biSub.m_moveInfo.m_score;

        // 黑棋（假设为AI层），取最大值
        if (IsBlack)
        {
            // 剪枝算法：当取得的值比上层（玩家层）已知的最小值还大时，剪掉该枝节（因为不可能被玩家层选用，玩家层只取最小值）
            if (TMoveInfo::EmiInvalid != uncle.m_moveState && uncle.m_score <= biSub.m_moveInfo.m_score)
            {
                mi = biSub.m_moveInfo;
                ++mi.m_score;
                break;
            }
            // 取最大值
            if (TMoveInfo::EmiInvalid == mi.m_moveState || mi.m_score < biSub.m_moveInfo.m_score)
                mi = biSub.m_moveInfo;
        }
        // 白棋（假设为玩家层），取最小值
        else
        {
            // 剪枝算法：当取得的值比上层（AI层）已知的最大值还小时，剪掉该枝节（因为不可能被AI层选用，AI层只取最大值）
            if (TMoveInfo::EmiInvalid != uncle.m_moveState && uncle.m_score >= biSub.m_moveInfo.m_score)
            {
                mi = biSub.m_moveInfo;
                --mi.m_score;
                break;
            }
            // 取最小值
            if (TMoveInfo::EmiInvalid == mi.m_moveState || mi.m_score > biSub.m_moveInfo.m_score)
                mi = biSub.m_moveInfo;
        }
    }
    return mi;
}
