#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QApplication>
#include "gamewindow.h"
#include "instruction.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_instructionbtn_clicked(); //连接游戏说明界面 槽函数

    void on_startbtn_clicked(); //连接游戏界面窗口 槽函数

private:
    Ui::MainWindow *ui;
    gamewindow *gw; //定义gamewindow窗口指针
    instruction *inst; //定义instruction窗口指针
};

#endif // MAINWINDOW_H
