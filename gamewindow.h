#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QMouseEvent>
#include <iostream>
#include <QString>

enum Gamestatus //定义游戏状态（枚举类）
{
    Playing,//游戏状态
    Win,//胜利
    Dead//死局
};

namespace Ui {
class gamewindow;
}

class gamewindow : public QDialog
{
    Q_OBJECT

public:  
    explicit gamewindow(QWidget *parent = nullptr);
    Gamestatus Gametatus;//游戏状态 枚举类
     void paintEvent(QPaintEvent *event);    //绘制棋盘事件
     void mouseMoveEvent(QMouseEvent *event);// 鼠标移动事件
     void mouseReleaseEvent(QMouseEvent *event);// 落子事件
     void initiategame();//初始化棋盘 重新开始 棋盘数组置0 下棋方转为白棋  白棋先行
        ~gamewindow();

private slots:
     void on_returnmainbtn_clicked();//返回主页面 槽函数

     void on_startagain_clicked();//重新开始 槽函数

     void on_regret_clicked();//悔棋 槽函数

     void on_rankinglist_clicked();//统计黑棋胜利次数 槽函数

     void on_saveboard_clicked();//保存棋局 槽函数

     void on_rankinglist_2_clicked();//统计白棋胜利次数 槽函数

private:
    Ui::gamewindow *ui;
    int board[15][15]={};//定义棋盘数组 白子置1 黑子置-1 空白置0
    int clickX, clickY; // 下棋点 坐标
    int PosX,PosY;//棋盘落子位置
    bool turn;//下棋方 白棋true 黑棋false
    int whitewintimes=0;//白方获胜次数
    int blackwintimes=0;//黑方获胜次数
    void changeturn(int row, int col); //更新棋盘信息，更换下棋方
    bool Winning(int row, int col); //判断输赢
    bool Dying(); //判断死局
};

#endif // GAMEWINDOW_H
