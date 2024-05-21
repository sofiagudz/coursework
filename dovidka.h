#ifndef DOVIDKA_H
#define DOVIDKA_H

#include <QDialog>

namespace Ui {
class Dovidka;
}

class Dovidka : public QDialog
{
    Q_OBJECT

public:
    explicit Dovidka(QWidget *parent = nullptr);
    ~Dovidka();

private:
    Ui::Dovidka *ui;
};

#endif // DOVIDKA_H
