#include <algorithm>
using namespace std;

#include "cmyview.h"

CMyView::CMyView(QWidget *parent) : QGraphicsView(parent)
{
    this->setScene(&m_scene);
}

void CMyView::SetLblWin(QLabel* l)
{
    LblWin = l;
}

void CMyView::StartGame(bool AiIsBlack, int AiDept)
{
    LblWin->setText("");
    m_moveInfo = TMoveInfo();
    TMoveInfo mi = m_ai.StartGame(AiIsBlack, AiDept);
    ReDrawData(this->size());
    DrawMoveInfo(mi);
}

bool CMyView::DrawMoveInfo(const TMoveInfo& mi)
{
    bool bResult = false;
    if (TMoveInfo::EmiInvalid != mi.m_moveState)
    {
        DrawStoneInfo(mi);
        bResult = true;
    }
    if (TMoveInfo::EmiIsWin == mi.m_moveState && nullptr != LblWin)
        LblWin->setText(mi.m_isBlack ? "黑胜！" : "白胜！");
    else if (mi.m_searchTime > 0)
        LblWin->setText(QString::number(mi.m_searchTime) + " - " + QString::number(mi.m_score));
    else
        LblWin->setText(" ");
    m_moveInfo = mi;
    DrawMoveFlag();
    return bResult;
}

void CMyView::DrawStoneInfo(const TStoneInfo& si)
{
    // 单元宽度
    QSize size = this->size();
    int iLenX = size.width() / 16;
    int iLenY = size.height() / 16;
    int iLen = min(iLenX, iLenY);
    // 画棋子
    QColor clrBlack(0, 0, 0);
    QColor clrWhite(255, 255, 255);
    this->scene()->addEllipse(iLenX * si.m_x - iLen / 2 + 2, iLenY * si.m_y - iLen / 2 + 2, iLen - 4, iLen - 4,
                              QPen(), QBrush(si.m_isBlack ? clrBlack : clrWhite));
}

void CMyView::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    this->setSceneRect(0, 0, size.width(), size.height());
    ReDrawData(size);
}

void CMyView::ReDrawData(QSize size)
{
    this->scene()->clear();
    m_moveFlag = nullptr;
    int iLenX = size.width() / 16;
    int iLenY = size.height() / 16;
    QPen pen;
    pen.setWidth(3);
    // 竖线
    for (int i = 1; i < 16; ++i)
        this->scene()->addLine(iLenX * i, iLenY, iLenX * i, iLenY * 15, 1 == i || 15 == i ? pen : QPen());
    // 横线
    for (int i = 1; i < 16; ++i)
        this->scene()->addLine(iLenX, iLenY * i, iLenX * 15, iLenY * i, 1 == i || 15 == i ? pen : QPen());
    // 星位
    this->scene()->addEllipse(iLenX * 4 - 4, iLenY * 4 - 4, 8, 8, QPen(), QBrush(QColor(0, 0, 0)));
    this->scene()->addEllipse(iLenX * 4 - 4, iLenY * 12 - 4, 8, 8, QPen(), QBrush(QColor(0, 0, 0)));
    this->scene()->addEllipse(iLenX * 8 - 4, iLenY * 8 - 4, 8, 8, QPen(), QBrush(QColor(0, 0, 0)));
    this->scene()->addEllipse(iLenX * 12 - 4, iLenY * 4 - 4, 8, 8, QPen(), QBrush(QColor(0, 0, 0)));
    this->scene()->addEllipse(iLenX * 12 - 4, iLenY * 12 - 4, 8, 8, QPen(), QBrush(QColor(0, 0, 0)));
    // 重画棋子
    TStoneInfoList stoneList;
    m_ai.GetStoneList(stoneList);
    for (TStoneInfo& stone: stoneList)
        DrawStoneInfo(stone);
    // 画落子标志
    DrawMoveFlag();
}

void CMyView::DrawMoveFlag(void)
{
    if (TMoveInfo::EmiInvalid != m_moveInfo.m_moveState)
    {
        // 单元宽度
        QSize size = this->size();
        int iLenX = size.width() / 16;
        int iLenY = size.height() / 16;
        // 画标志
        if (nullptr != m_moveFlag)
            this->scene()->removeItem(m_moveFlag);
        m_moveFlag = this->scene()->addEllipse(iLenX * m_moveInfo.m_x - 4, iLenY * m_moveInfo.m_y - 4,
                                               8, 8, QPen(), QBrush(QColor(255, 0, 0)));
    }
}

void CMyView::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    QSize size = this->size();
    // 单元宽度
    int iLenX = size.width() / 16;
    int iLenY = size.height() / 16;
    // 计算在棋盘上的坐标
    int iX = int(0.5 + pos.x() * 1.0 / iLenX);
    int iY = int(0.5 + pos.y() * 1.0 / iLenY);
    // 玩家落子
    TMoveInfo mi = m_ai.PlayerMove(iX, iY);
    if (TMoveInfo::EmiInvalid != mi.m_moveState) DrawMoveInfo(mi);

    QGraphicsView::mousePressEvent(event);
}

void CMyView::OnTimer(void)
{
    // AI落子
    TMoveInfo mi = m_ai.AIMove();
    if (TMoveInfo::EmiInvalid != mi.m_moveState) DrawMoveInfo(mi);
}
