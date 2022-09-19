#ifndef STAT_H
#define STAT_H

#include <QDialog>
#include "mydb.h"


namespace Ui {
class Stat;
}

class Stat : public QDialog
{
    Q_OBJECT

public:
    explicit Stat(QWidget *parent = nullptr);
    ~Stat();
    void Show();
private:
    Ui::Stat *ui;
};

#endif // STAT_H
