#include "client.h"

client::client()
{

}
client::client(int id,QString nom,QString prenom,QString sexe,QDate cdate){
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->cdate=cdate;
    this->sexe=sexe;
}
int client::get_id(){return id;}
QString client::get_nom(){return nom;}
QString client::get_prenom(){return prenom;}
QDate client::get_date(){return cdate;}
QString client::get_sexe(){return sexe;}

bool client::ajouter(){
    QSqlQuery q;
    q.prepare("insert into client values(:id,:nom,:prenom,:sexe,:date)");
    q.bindValue(":id",id);
    q.bindValue(":nom",nom);
    q.bindValue(":sexe",sexe);
    q.bindValue(":date",cdate);
    return q.exec();
}
bool client::supprimer(int a)
{
    QSqlQuery q;
    QString res=QString::number(a);
    q.prepare("delete from client where id=:id");
    q.bindValue(":id",res);
    return q.exec();
}
bool client::modifier(int id)
{

    QSqlQuery q;
    q.prepare("update client set id=:id,nom=:nom,prenom=:prenom,sexe=:sexe,date=:date where id=:id");
    q.bindValue(":id",id);
    q.bindValue(":nom",nom);
    q.bindValue(":prenom",prenom);
    q.bindValue(":sexe",sexe);
    q.bindValue(":date",cdate);

   return q.exec();


}
 QSqlQueryModel * client::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from client");

    return model;
}

/* QSqlQueryModel * guichet::affichercatId()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select id from guichet");

    return model;
}
int guichet::nbr_aide(int id){
    QSqlQuery q;
    q.prepare("select sum(quantite) as total from ticket where guichet_id=:id");
    q.bindValue(":id",id);
    if(q.exec())
    {
       while(q.next()){
    int nbr = q.value(0).toInt();
    return nbr;
       }}
}
*/
