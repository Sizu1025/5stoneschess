#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QPen>
#include <QPainter>
#include <QMessageBox>
#include <math.h>
#include <QDebug>
#include <QFileDialog>
#include <QDialog>
#include <QLabel>
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QString>

// 棋盘尺寸15*15格 格子尺寸40*40 棋子半径15 棋盘上下左右间距30 棋盘高度 660

gamewindow::gamewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gamewindow)
{
    ui->setupUi(this);
    this->setWindowTitle("五子棋-双人对决");//设置窗口标题
    this->setFixedSize(810,660);// 设置窗口尺寸
    this->setAutoFillBackground(true);
    setMouseTracking(true); //开启鼠标鼠标监听事件
    initiategame();//初始化游戏
}

void gamewindow::initiategame()//初始化棋盘
{
    Gametatus=Playing;//设置游戏状态
    for (int i = 0; i < 15; i++)//初始化数组置0
    {
        for (int j = 0; j < 15; j++)
        {
            board[i][j]=0;
        }
    }
    turn = true;//白棋先行
    update();//重绘
}

void gamewindow::changeturn(int row, int col)//更新棋盘信息，更换下棋方
{
    if (turn)
    {
        board[row][col] = 1;//数组储存为白棋
    }
    else
    {
        board[row][col] = -1;//数组储存为黑棋
    }
    turn = !turn;//换另一方下棋
}

bool gamewindow::Winning(int row, int col)//判断输赢 根据当前落子情况遍历5个棋子
{
    for (int i = 0; i < 5; i++) // 水平方向
    {
        if (col - i > 0 && col - i + 4 < 15 && board[row][col - i] == board[row][col - i + 1] && board[row][col - i] ==board[row][col - i + 2] && board[row][col - i] == board[row][col - i + 3] && board[row][col - i] == board[row][col - i + 4])
            return true;
    }  
    for (int i = 0; i < 5; i++) //垂直方向
    {
        if (row - i > 0 && row - i + 4 < 15 && board[row - i][col] == board[row - i + 1][col] && board[row - i][col] ==board[row - i + 2][col] && board[row - i][col] == board[row - i + 3][col] && board[row - i][col] == board[row - i + 4][col])
            return true;
    }
    for (int i = 0; i < 5; i++) //左倾斜方向
    {
        if (row + i < 15 && row + i - 4 > 0 && col - i > 0 && col - i + 4 < 15 && board[row + i][col - i] == board[row + i - 1][col - i + 1] && board[row + i][col - i] == board[row + i - 2][col - i + 2] && board[row + i][col - i] ==board[row + i - 3][col - i + 3] && board[row + i][col - i] == board[row + i - 4][col - i + 4])
            return true;
    }
    for (int i = 0; i < 5; i++)//右倾斜方向
    {
        if (row - i > 0 && row - i + 4 <15 && col - i > 0 && col - i + 4 < 15&& board[row - i][col - i] == board[row - i + 1][col - i + 1] && board[row - i][col - i] == board[row - i + 2][col - i + 2] && board[row - i][col - i] == board[row - i + 3][col - i + 3] && board[row - i][col - i] == board[row - i + 4][col - i + 4])
            return true;
    }
    return false;
}

bool gamewindow::Dying()//判断死局
{   
    for (int i = 1; i <15; i++)//棋盘元素满置
    {
        for (int j = 1; j <15; j++)
        {
            if (board[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}


void gamewindow::paintEvent(QPaintEvent *event)//绘图事件
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    QPen pen;  // 绘制棋盘框
    pen.setColor(QColor("#8D5940"));
    pen.setWidth(7);
    painter.setPen(pen);
    QBrush brush;
   brush.setColor(QColor("#EEC054"));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(20,40,600,600);
    pen.setColor(Qt::black);//绘制棋盘
    pen.setWidth(2);
    painter.setPen(pen);
    for (int i = 0; i <15; i++)//绘制棋盘格15*15
    {
        painter.drawLine(40+40*i,60,40+40*i,620);
        painter.drawLine(40,60+40*i,600,60+40*i);
    }
    brush.setColor(Qt::black);//绘制棋盘下棋标记点
    painter.setBrush(brush);
    painter.drawRect(155,175,10,10);
    painter.drawRect(475,175,10,10);
    painter.drawRect(155,495,10,10);
    painter.drawRect(475,495,10,10);
    painter.drawRect(315,335,10,10);    
    if (clickX > 0 && clickX < 15 && clickY > 0 && clickY <15 && board[clickX][clickY] == 0)// 落子标记绘制
    {
        if (turn)
        {
            brush.setColor(Qt::white);//白棋标志
        }
        else
        {
            brush.setColor(Qt::black);//黑棋标志
        }
        painter.setBrush(brush);
        painter.drawRect(40 + 40 * clickY - 6 / 2, 20 + 40 * clickX - 6 / 2, 6, 6);
    }
            for (int i = 0; i < 15; i++) // 绘制棋子
            {
                for (int j = 0; j < 15; j++)
                {
                    if (board[i][j] == 1)
                    {
                        brush.setColor(Qt::white);
                        painter.setBrush(brush);
                        painter.drawEllipse(40 + 40 * j - 15, 20 + 40 * i - 15, 15 * 2, 15 * 2);

                    }
                    else if (board[i][j] == -1)
                    {
                        brush.setColor(Qt::black);
                        painter.setBrush(brush);
                        painter.drawEllipse(40 + 40 * j - 15, 20 + 40 * i - 15, 15 * 2, 15 * 2);
                    }
                }
            }
}

void gamewindow::mouseMoveEvent(QMouseEvent *event)//鼠标移动事件
{ 
    int x = event->x(); //鼠标追踪确定落子标记
    int y = event->y();
    if (x >= (40 + 40 / 2) && x <  (660 - 40 - 50) && y >= (40 + 30 + 40 / 2) && y <  (660 - 40))
    {
        clickX = (event->y() - 10) / 40;
        clickY = (event->x() - 15) / 40;
    }
    update();
}

void gamewindow::mouseReleaseEvent(QMouseEvent *event)//落子事件
{
    if (clickX != -1 && clickY != -1 && board[clickX][clickY] == 0)//落子
   {
     changeturn(clickX , clickY);
     PosX=clickX;
     PosY=clickY;
     update();
    } 
  if (clickX > 0 && clickX < 15 && clickY > 0 && clickY < 15 && (board[clickX][clickY] != 0)) //判断输赢
    {
        if (Winning(clickX, clickY) && Gametatus == Playing)
        {
            Gametatus= Win;
            QMessageBox::StandardButton button;
           if (board[clickX][clickY] == 1)
            {
               button =QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("白方胜利！"));
               whitewintimes++;//胜利次数计数器
            }
            else if (board[clickX][clickY] == -1)
            {
             button =QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("黑方胜利！"));
             blackwintimes++;//胜利次数计数器
           }       
          if (button == QMessageBox::Ok) //重置初始化游戏
       {
            initiategame();
            Gametatus == Playing;
          }
        }
       } 
    if (Dying())//判断死局
   {
        QMessageBox::StandardButton button = QMessageBox::information(this, "提示", "死局!请重新开始游戏！");
        if (button == QMessageBox::Ok)
       {
            initiategame();
            Gametatus =Playing;
        }
    }
}

void gamewindow::on_startagain_clicked()//重新开始
{
    QMessageBox::StandardButton button = QMessageBox::information(this, "提示", "是否重新开始？");
    if (button == QMessageBox::Ok)
   {
        initiategame();
        Gametatus =Playing;
   }
}

void gamewindow::on_regret_clicked()//悔棋
{
    turn=board[PosX][PosY];//下棋方不变
    board[PosX][PosY]=0;//棋盘数据清零
    update();//重绘
    }

void gamewindow::on_rankinglist_clicked()//黑棋获胜次数
{
    QMessageBox::StandardButton button = QMessageBox::information(this, "黑棋获胜次数", "是否保存？");
    if (button == QMessageBox::Ok)
   {
    QString filename = QFileDialog::getSaveFileName(this, tr("保存路径节点"), "", tr("Text files(*.txt)"));
      if(filename.isEmpty())
          return;
      else
      {
          QFile file(filename);
          if(! file.open(QIODevice::WriteOnly | QIODevice::Text))
          {
              QMessageBox::warning(this, tr("读取文件"), tr("无法打开文件：\n%1").arg(filename));
              return;
          }
              QDataStream stream(&file);
              QTextStream in(&file);
              stream<<"黑棋获胜次数:";
              in<<blackwintimes;
              }
      }
}

void gamewindow::on_saveboard_clicked()//保存棋局
{
    QMessageBox::StandardButton button = QMessageBox::information(this, "棋局", "是否保存？");
    if (button == QMessageBox::Ok)
   {
        QPixmap pixmap=this->grab(QRect(10,30,620,620));
        QString filename = QFileDialog::getSaveFileName(this,QStringLiteral("保存图片"),"../5stineschess/", "Image File(*.jpg)");
        if(filename.length()>0)
        {
            pixmap.save(filename);
        }
   }
}

void gamewindow::on_rankinglist_2_clicked()//白棋获胜次数
{
    QMessageBox::StandardButton button = QMessageBox::information(this, "白棋获胜次数", "是否保存？");
    if (button == QMessageBox::Ok)
   {
    QString filename = QFileDialog::getSaveFileName(this, tr("保存路径节点"), "", tr("Text files(*.txt)"));
      if(filename.isEmpty())
          return;
      else
      {
          QFile file(filename);
          if(! file.open(QIODevice::WriteOnly | QIODevice::Text))
          {
              QMessageBox::warning(this, tr("读取文件"), tr("无法打开文件：\n%1").arg(filename));
              return;
          }
              QDataStream stream(&file);
              QTextStream in(&file);
              stream<<"白棋获胜次数:";
              in<<whitewintimes;
              }
      }
}

gamewindow::~gamewindow()
{
    delete ui;
}

