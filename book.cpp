#include "book.h"
#include "ui_book.h"

Book::Book(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Book)
{
    ui->setupUi(this);
    //connect(ui->pushButton,SIGNAL(clicked()), this, SIGNAL(myClicked()));
   connect(this, SIGNAL(mysignal()), parent, SLOT(updateUI()));
}

Book::~Book()
{
    delete ui;
}

void Book::Show()
{
    updateUI();
    show();
}

void Book::updateUI()
{
    ui->cmbSlots->clear();

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select Slot from parking where Available='Y'");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText(query.lastError().text());
    }
    else{
        qDebug() << "read was successful "<< query.lastQuery();
       }

    while(query.next())
    {

        ui->cmbSlots->addItem(query.value(0).toString());
    }

}

void Book::on_pushButton_clicked()
{
    QString sSlot = ui->cmbSlots->currentText();

    ui->cmbSlots->clear();
    ui->lblInfo->setText("");

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("update parking set Available='N' where Slot='" + sSlot + "'");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText(query.lastError().text());
    }
    else{
        if(query.numRowsAffected() > 0)
        {
            qDebug() << "Update was successful "<< query.lastQuery();
            ui->lblInfo->setText("Update was successful!");
        }
        else {
            ui->lblInfo->setText("Update was not successful!");
        }
       }
    updateUI();
    emit mysignal();
}
