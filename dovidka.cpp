#include "dovidka.h"
#include "ui_dovidka.h"

Dovidka::Dovidka(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dovidka)
{
    ui->setupUi(this);
}

Dovidka::~Dovidka()
{
    delete ui;
}
