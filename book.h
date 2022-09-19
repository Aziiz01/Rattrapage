#ifndef BOOK_H
#define BOOK_H

#include <QDialog>
#include "mydb.h"

namespace Ui {
class Book;
}

class Book : public QDialog
{
    Q_OBJECT

public:
    explicit Book(QWidget *parent = nullptr);
    ~Book();
    void Show();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Book *ui;
    void updateUI();

signals:
 void mysignal();
};

#endif // BOOK_H
