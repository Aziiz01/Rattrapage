#include "stat.h"
#include "ui_stat.h"



Stat::Stat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stat)
{
    ui->setupUi(this);

}

Stat::~Stat()
{
    delete ui;
}

void Stat::Show()
{
    show();
}
