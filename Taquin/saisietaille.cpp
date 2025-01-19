#include "saisietaille.h"
#include "ui_saisietaille.h"

saisietaille::saisietaille(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saisietaille)
{
    ui->setupUi(this);
ui->pushButton->setIcon(QIcon(style()->standardIcon(QStyle::SP_DialogCancelButton)));
ui->pushButton_2->setIcon(QIcon(style()->standardIcon(QStyle::SP_DialogOkButton)));
 this->setWindowIcon(QIcon(":/icon/annexe/240px-15-puzzle.png"));
this->setFixedSize(width(),height());

}

saisietaille::~saisietaille()
{
    delete ui;
}

int saisietaille::gettaille() const
{
    return  ui->_taille->value();
}


void saisietaille::settaille(int a)
{
     ui->_taille->setValue(a);
}


