#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQueryModel>
#include <QDate>



class client
{
public:
    client();
    client(int,QString,QString,QString,QDate);
    int get_id();
    QString get_nom();
    QString get_prenom();
    QString get_sexe();
    QDate get_date();
    bool ajouter();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel * afficher();
    QSqlQueryModel *affichercatId();

private:
int id;
QString nom,prenom,sexe;
QDate cdate;
};

#endif // CLIENT_H
