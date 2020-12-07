#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("五子棋小游戏");//设置窗口标题
    this->setFixedSize(520,550);//设置窗口大小
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_instructionbtn_clicked()  //跳转游戏说明界面
{
    this->close();
    instruction *inst=new instruction;
    inst->show();
}

void MainWindow::on_startbtn_clicked() //跳转游戏界面
{
    this->close();
    gamewindow *gw=new gamewindow;
    gw->show();
}


void instruction::on_returnbtn_clicked()//返回主页面
{
    MainWindow* mw = new MainWindow;
    mw->show();
    this->hide();
}

void gamewindow::on_returnmainbtn_clicked()//返回主页面
{
    MainWindow* mw = new MainWindow;
    mw->show();
    this->hide();
}
