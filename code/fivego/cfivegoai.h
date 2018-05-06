#pragma once

#include <vector>
#include <map>
#include <ctime>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstring>
#include <functional>
using namespace std;

namespace FiveGo
{
    //  棋盘尺寸
    constexpr int c_boardSize = 15;
    constexpr int c_fullScore = 10000;

    // 计分标准：+空；*黑子；o白子
    struct TScoreUnit
    {
        const char* m_info = nullptr;       // 类型信息
        int m_fp = 0, m_bp = 0;             // 前、后空位
        bool m_swap = true;                 // 对称的图形
        int m_score = 0;                    // 计分

        TScoreUnit(const char* inf, int fp, int bp, bool swp, int sco) : m_info(inf), m_fp(fp), m_bp(bp), m_swap(swp), m_score(sco) {}
    };
    const TScoreUnit c_ScoreList[] =
    {
        // 活一
          TScoreUnit{"*", 1, 1, true, 1}
        , TScoreUnit{"o", 1, 1, true, -1}
        // 活二
        , TScoreUnit{"**", 1, 1, true, 10}
        , TScoreUnit{"*+*", 1, 1, true, 10}
        , TScoreUnit{"oo", 1, 1, true, -10}
        , TScoreUnit{"o+o", 1, 1, true, -10}
        // 死二
        , TScoreUnit{"o**", 0, 1, false, 1}
        , TScoreUnit{"o*+*", 0, 1, false, 1}
        , TScoreUnit{"*oo", 0, 1, false, -1}
        , TScoreUnit{"*o+o", 0, 1, false, -1}
        // 活三
        , TScoreUnit{"***", 1, 1, true, 100}
        , TScoreUnit{"**+*", 1, 1, false, 100}
        , TScoreUnit{"ooo", 1, 1, true, -100}
        , TScoreUnit{"oo+o", 1, 1, false, -100}
        // 死三
        , TScoreUnit{"o***", 0, 2, false, 10}
        , TScoreUnit{"o**+*", 0, 1, false, 10}
        , TScoreUnit{"*ooo", 0, 2, false, -10}
        , TScoreUnit{"*oo+o", 0, 1, false, -10}
        // 活四
        , TScoreUnit{"****", 1, 1, true, 1000}
        , TScoreUnit{"oooo", 1, 1, true, -1000}
        // 冲四
        , TScoreUnit{"o****", 0, 1, false, 100}
        , TScoreUnit{"**+**", 0, 0, true, 110}
        , TScoreUnit{"***+*", 0, 0, false, 120}
        , TScoreUnit{"*oooo", 0, 1, false, -100}
        , TScoreUnit{"oo+oo", 0, 0, true, -110}
        , TScoreUnit{"ooo+o", 0, 0, false, -120}
        // 连五
        , TScoreUnit{"*****", 0, 0, true, c_fullScore}
        , TScoreUnit{"ooooo", 0, 0, true, -c_fullScore}
    };

    // 棋子信息
    struct TStoneInfo
    {
        bool m_isBlack = true;
        int m_x = 0, m_y = 0;

        TStoneInfo(int x = 0, int y = 0, bool b = true) : m_isBlack(b), m_x(x), m_y(y) {}
    };
    typedef vector<TStoneInfo> TStoneInfoList;

    // 落子信息
    struct TMoveInfo : public TStoneInfo
    {
        enum EMoveState
        {
            EmiInvalid,         // 无效
            EmiValid,           // 有效
            EmiIsWin            // 胜利
        };
        EMoveState m_moveState = EmiInvalid;
        unsigned int m_searchTime = 0;
        int m_score = 0;
    };

    // 盘面信息
    struct TBoardInfo
    {
        TMoveInfo m_moveInfo;
        // 子力范围
        int m_minX = 0, m_minY = 0, m_maxX = 0, m_maxY = 0;
        // +空；*黑子；o白子
        char m_board[c_boardSize][c_boardSize] = {{0}};
    };

    // 五子棋AI
    class CFiveGoAI
    {
    public:
        CFiveGoAI();

        // 开始游戏
        TMoveInfo StartGame(bool AiIsBlack = true, int AiDept = 4);
        // 玩家落子
        TMoveInfo PlayerMove(int x, int y);
        // AI落子
        TMoveInfo AIMove(void);
        // 棋子列表
        void GetStoneList(TStoneInfoList&) const;

    protected:
        // 设置盘面状态
        void SetBoardState(TBoardInfo& bi);
        // 检查落子是否有效
        bool CheckMove(const TBoardInfo& bi, int x, int y, bool IsBlack);
        // 检查是否获胜
        bool CheckWin(const TBoardInfo& bi, int x, int y, bool IsBlack);
        // AI算法
        TMoveInfo AI(const TBoardInfo& bi, int dept);
        // 评分算法
        int Score(const TBoardInfo& bi);
        // 极大极小值搜索算法
        TMoveInfo MaxMin(const TBoardInfo& bi, int dept, bool IsBlack, TMoveInfo uncle);

    private:
        bool m_IsStart = false;                         // 是否开始
        bool m_AiIsBlack = true;                        // AI执黑棋
        bool m_CurrentIsAi = false;                     // 当前该AI执行
        int m_AiDept = 4;                               // 搜索深度
        TBoardInfo m_boardInfo;                         // 盘面信息
        int m_value[c_boardSize][c_boardSize] = {{0}};  // 盘面各点的价值

    };
}
