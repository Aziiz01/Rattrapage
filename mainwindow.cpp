#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "cancel.h"
#include "book.h"
#include <QPdfWriter>
#include <QDesktopServices>
#include <QPainter>
#include <QRegExpValidator>
#include <QIntValidator>
#include <QMessageBox>
#include "stat.h"
#include "mydb.h"
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent) ,
  ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_3->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie
    ui->lineEdit->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
    ui->lineEdit_2->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
    ptrBook = new Book(this);
    ptrCancel = new Cancel(this);

    connect(ptrBook, &Book::mysignal, this, &MainWindow::updateUI);
    connect(ptrCancel, &Cancel::mysignal1, this, &MainWindow::updateUI);

    updateUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int id = ui->lineEdit_3->text().toInt();
    QString nom = ui->lineEdit->text();
    QString prenom =ui->lineEdit_2->text();
    QString sexe =ui->comboBox->currentText();
    QDate cdate = ui->dateEdit->date();

    client s(id,nom,prenom,sexe,cdate);
        bool test = s.ajouter();
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("CLIENT ADD "),
                                      QObject::tr("CLIENT ADDED SUCCESSFULLY.\n"), QMessageBox::Ok);
        ui->tableView->setModel(c.afficher());
         ui->lineEdit->clear();
         ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->comboBox->clear();
        ui->dateEdit->clear();
       // hideElements();


    }
    else{
        QMessageBox::information(nullptr, QObject::tr("CLIENT ADD "),
                                      QObject::tr("ERROR.\n"), QMessageBox::Ok);

}

}

void MainWindow::affichageDonnee(){
    QSqlQuery requete; int ligne(0);
    requete.exec("select * from client ");
    while(requete.next())
    {
        ligne=requete.value(0).toInt();
    }
   // QMessageBox::warning(this,"",QString::number((ligne)));
    model = new QStandardItemModel(ligne,5);
    int row(0);
    requete.exec("select id,nom,prenom,sexe,cdate from client");
    while(requete.next()){
    for(int j=0;j<5;j++)
    {
        QStandardItem *item=new QStandardItem(requete.value(j).toString());
        model->setItem(row,j,item);

    }
    row++; }
    model->setHeaderData(0,Qt::Horizontal,"Id");
    model->setHeaderData(0,Qt::Horizontal,"Nom");
    model->setHeaderData(0,Qt::Horizontal,"Prenom");
    model->setHeaderData(0,Qt::Horizontal,"Sexe");
    model->setHeaderData(0,Qt::Horizontal,"Date");


}

void MainWindow::on_pushButton_2_clicked()
    {
        int id= ui->lineEdit_3->text().toInt();
        QString nom= ui->lineEdit->text();
        QString prenom= ui->lineEdit_2->text();
        QString sexe =ui->comboBox->currentText();
        QDate cdate =ui->dateEdit->date();
         bool test = false;
         client cp(id,nom,prenom,sexe,cdate);
        test = cp.modifier(id);
        if(test){
            ui->tableView->setModel(c.afficher());
            //hideElements();
            QMessageBox::information(nullptr, QObject::tr("CLIENT MODIFY"),
                                          QObject::tr("CLIENT MODIFIED SUCCESSFULY .\n"
                                                      "Click Ok to exit."), QMessageBox::Ok);

        }
        else{
            ui->tableView->setModel(c.afficher());
            //hideElements();

            QMessageBox::information(nullptr, QObject::tr("CLIENT MODIFY"),
                                          QObject::tr("ERROR !\n"), QMessageBox::Cancel);

        }



}

void MainWindow::on_pushButton_3_clicked()
{
    int id = ui->lineEdit_4->text().toInt();
    bool test  = c.supprimer(id);
    if(test){
        //hideElements();
        ui->tableView->setModel(c.afficher());

        QMessageBox::information(nullptr, QObject::tr("CLIENT Delete"),
                                      QObject::tr("Cliend deleted SUCCESSFULY .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);



    }
    else{
       // hideElements();
        ui->tableView->setModel(c.afficher());

        QMessageBox::information(nullptr, QObject::tr("CLIENT delete"),
                                      QObject::tr("ERROR .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);


    }
}

void MainWindow::on_pushButton_4_clicked()
{
        //QDateTime datecreation = date.currentDateTime();
        //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
               QPdfWriter pdf("C:/Users/HP/Deskto/pdf.pdf");
               QPainter painter(&pdf);
              int i = 4000;
                   painter.setPen(Qt::blue);
                   painter.setFont(QFont("Arial", 30));
                   painter.drawText(1100,1200,"Liste Des Employes");
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Arial", 50));
                  // painter.drawText(1100,2000,afficheDC);
                   painter.drawRect(100,100,7300,2600);
                   //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                   painter.drawRect(0,3000,9600,500);
                   painter.setFont(QFont("Arial", 9));
                   painter.drawText(200,3300,"ID");
                   painter.drawText(1700,3300,"NOM");
                   painter.drawText(3200,3300,"PRENOM");
                   painter.drawText(4900,3300,"SEXE");
                   painter.drawText(6600,3300,"CDATE");
                   QSqlQuery query;
                   query.prepare("select * from CLIENT");
                   query.exec();
                   while (query.next())
                   {
                       painter.drawText(200,i,query.value(0).toString());
                       painter.drawText(1700,i,query.value(1).toString());
                       painter.drawText(3200,i,query.value(2).toString());
                       painter.drawText(4900,i,query.value(3).toString());
                       painter.drawText(6600,i,query.value(4).toString());
                      i = i + 700;
                   }
                   int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                       if (reponse == QMessageBox::Yes)
                       {
                          QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/HP/Desktop/logopdf.png"));
                           painter.end();
                       }
                       if (reponse == QMessageBox::No)
                       {
                            painter.end();
                       }
    }
void MainWindow::updateUI()
{
    qDebug() << "===== in updateUI() ====";
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("select Slot, Available from parking");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
//ui->lblInfo->setText(query.lastError().text());
    }
    else{
        qDebug() << "read was successful "<< query.lastQuery();
    }

    int no = 1;
    while(query.next())
    {
        QString sLabel = "lblSlot" + query.value(0).toString();
        QLabel * ptr = this->findChild<QLabel*>(sLabel);
        if(ptr!=nullptr)
        {
            if(query.value(1).toString().compare("N") == 0)
            {
                //int no = (qrand() % ((6 + 1) - 1) + 1);
                QString sBike = "bike" + QString::number(no) + ".jpg";
                QPixmap pm(":/assets/images/"+sBike);
                ptr->setPixmap(pm);
                ptr->setScaledContents(true);
                qDebug()<<query.value(0).toString() << " : is booked";
            }
            else
            {
                ptr->clear();
                ptr->setText("Slot "+query.value(0).toString());
            }


        }
        qDebug()<<query.value(0).toString()<< query.value(1).toString();
        no>=6?no=1:no++;
    }

}

void MainWindow::on_btnCancel_clicked()
{
    ptrCancel->Show();
}

void MainWindow::on_btnBook_clicked()
{
    ptrBook->show();
}

void MainWindow::Show()
{
    qDebug() << "in MainWindow::Show()";
}


void MainWindow::on_pushButton_5_clicked()
{
ptrStat->Show();
}
