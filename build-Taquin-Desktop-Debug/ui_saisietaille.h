/********************************************************************************
** Form generated from reading UI file 'saisietaille.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAISIETAILLE_H
#define UI_SAISIETAILLE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_saisietaille
{
public:
    QSpinBox *_taille;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *saisietaille)
    {
        if (saisietaille->objectName().isEmpty())
            saisietaille->setObjectName(QString::fromUtf8("saisietaille"));
        saisietaille->setWindowModality(Qt::NonModal);
        saisietaille->setEnabled(true);
        saisietaille->resize(251, 171);
        QIcon icon;
        icon.addFile(QString::fromUtf8("annexes/puzzle.png"), QSize(), QIcon::Normal, QIcon::Off);
        saisietaille->setWindowIcon(icon);
        saisietaille->setSizeGripEnabled(false);
        _taille = new QSpinBox(saisietaille);
        _taille->setObjectName(QString::fromUtf8("_taille"));
        _taille->setGeometry(QRect(170, 70, 51, 31));
        _taille->setMinimum(3);
        _taille->setMaximum(20);
        label = new QLabel(saisietaille);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 70, 131, 41));
        pushButton = new QPushButton(saisietaille);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 140, 89, 25));
        pushButton_2 = new QPushButton(saisietaille);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 140, 89, 25));

        retranslateUi(saisietaille);
        QObject::connect(pushButton, SIGNAL(clicked()), saisietaille, SLOT(reject()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), saisietaille, SLOT(accept()));

        QMetaObject::connectSlotsByName(saisietaille);
    } // setupUi

    void retranslateUi(QDialog *saisietaille)
    {
        saisietaille->setWindowTitle(QCoreApplication::translate("saisietaille", "New part ?", nullptr));
        label->setText(QCoreApplication::translate("saisietaille", "Taille du Taquin", nullptr));
        pushButton->setText(QCoreApplication::translate("saisietaille", "Annuler", nullptr));
        pushButton_2->setText(QCoreApplication::translate("saisietaille", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class saisietaille: public Ui_saisietaille {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAISIETAILLE_H
