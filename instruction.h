#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QDialog>

namespace Ui {
class instruction;
}

class instruction : public QDialog
{
    Q_OBJECT

public:
    explicit instruction(QWidget *parent = nullptr);
    ~instruction();

private slots:
    void on_returnbtn_clicked();//返回主页面 槽函数

private:
    Ui::instruction *ui;
};

#endif // INSTRUCTION_H
