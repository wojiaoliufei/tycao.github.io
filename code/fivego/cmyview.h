#pragma once

#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QtGui>

#include "cfivegoai.h"
using namespace FiveGo;

class CMyView : public QGraphicsView
{
public:
    explicit CMyView(QWidget *parent = Q_NULLPTR);

    void SetLblWin(QLabel*);
    void StartGame(bool AiIsBlack = true, int AiDept = 4);
    void OnTimer(void);

protected:
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

    void ReDrawData(QSize size);
    bool DrawMoveInfo(const TMoveInfo& mi);
    void DrawStoneInfo(const TStoneInfo& si);
    void DrawMoveFlag(void);

private:
    QGraphicsScene m_scene;
    CFiveGoAI m_ai;
    QLabel *LblWin = nullptr;
    TMoveInfo m_moveInfo;
    QGraphicsItem* m_moveFlag = nullptr;
};
