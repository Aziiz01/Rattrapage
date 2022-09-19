#ifndef CANCEL_H
#define CANCEL_H

#include <QDialog>
#include "mydb.h"

namespace Ui {
class Cancel;
}

class Cancel : public QDialog
{
    Q_OBJECT

public:
    explicit Cancel(QWidget *parent = nullptr);
    ~Cancel();
    void Show();

private slots:
    void on_btnUpdate_clicked();

private:
    Ui::Cancel *ui;
    void updateUI();

signals:
 void mysignal1();

};

#endif // CANCEL_H
