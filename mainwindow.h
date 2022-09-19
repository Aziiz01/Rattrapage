#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mydb.h"
#include "client.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "book.h"
#include "cancel.h"
#include "stat.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Show();


private slots:
    void on_pushButton_clicked();
void affichageDonnee();

void on_pushButton_2_clicked();

void on_pushButton_3_clicked();

void on_pushButton_4_clicked();
void on_btnCancel_clicked();

void on_btnBook_clicked();

void on_pushButton_5_clicked();

private :
    Ui::MainWindow *ui;
    client c;
    QStandardItemModel *model;
    void updateUI();
    Book *ptrBook;
    Cancel *ptrCancel;
    Stat *ptrStat;
};

#endif // MAINWINDOW_H
