#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->gridLayoutWidget);
    ui->graphicsView->SetLblWin(ui->LblWin);
    QTimer *dt = new QTimer(this);
    connect(dt, SIGNAL(timeout()), this, SLOT(on_timeout()));
    dt->start(300);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BtnBegin_clicked()
{
    ui->graphicsView->StartGame(ui->RdbBlack->isChecked(), ui->TxtDept->value());
}

void MainWindow::on_timeout()
{
    ui->graphicsView->OnTimer();
}
