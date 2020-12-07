#include "instruction.h"
#include "ui_instruction.h"

instruction::instruction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::instruction)
{
    ui->setupUi(this);
    setWindowTitle("游戏说明");//设置窗口标题
}

instruction::~instruction()
{
    delete ui;
}


