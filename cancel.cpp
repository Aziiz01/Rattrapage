#include "cancel.h"
#include "ui_cancel.h"

Cancel::Cancel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cancel)
{
    ui->setupUi(this);
}

Cancel::~Cancel()
{
    delete ui;
}

void Cancel::Show()
{
    updateUI();
    show();
}

void Cancel::updateUI()
{
    ui->cmbSlots->clear();
    //ui->lblInfo->setText("");

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select Slot from parking where Available='N'");

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

    if(ui->cmbSlots->count()<=0)
        ui->btnUpdate->setEnabled(false);


}

void Cancel::on_btnUpdate_clicked()
{
    qDebug() << " in Cancel::update()";
    QString sSlot = ui->cmbSlots->currentText();

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("update parking set Available='Y' where Slot='" + sSlot + "' ");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText(query.lastError().text());
    }
    else{
        if(query.numRowsAffected() > 0)
        {
            ui->lblInfo->setText("Slot is Available now");
            qDebug() << "last query was : "<< query.lastQuery();
            updateUI();
        }
        else
        {
            ui->lblInfo->setText("Unable to update");
            qDebug() << "unable to update : " << query.lastQuery();
        }
    }

     emit mysignal1();
}
