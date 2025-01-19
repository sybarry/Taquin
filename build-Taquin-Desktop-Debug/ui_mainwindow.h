/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *_nouvpartie;
    QAction *_chargpart;
    QAction *_quitpart;
    QAction *_sauvpart;
    QAction *_imgor;
    QAction *_imgfo;
    QAction *_imgarb;
    QAction *_imgre;
    QAction *action_A_propos_de_QT;
    QAction *action_A_Propos_de_Taquin;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFicher;
    QMenu *menuFond;
    QMenu *menuaide;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(530, 333);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../build-projet_diga-Desktop-Debug/puzzle.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLocale(QLocale(QLocale::French, QLocale::France));
        MainWindow->setIconSize(QSize(60, 60));
        _nouvpartie = new QAction(MainWindow);
        _nouvpartie->setObjectName(QString::fromUtf8("_nouvpartie"));
        _chargpart = new QAction(MainWindow);
        _chargpart->setObjectName(QString::fromUtf8("_chargpart"));
        _quitpart = new QAction(MainWindow);
        _quitpart->setObjectName(QString::fromUtf8("_quitpart"));
        _sauvpart = new QAction(MainWindow);
        _sauvpart->setObjectName(QString::fromUtf8("_sauvpart"));
        _imgor = new QAction(MainWindow);
        _imgor->setObjectName(QString::fromUtf8("_imgor"));
        _imgfo = new QAction(MainWindow);
        _imgfo->setObjectName(QString::fromUtf8("_imgfo"));
        _imgarb = new QAction(MainWindow);
        _imgarb->setObjectName(QString::fromUtf8("_imgarb"));
        _imgre = new QAction(MainWindow);
        _imgre->setObjectName(QString::fromUtf8("_imgre"));
        action_A_propos_de_QT = new QAction(MainWindow);
        action_A_propos_de_QT->setObjectName(QString::fromUtf8("action_A_propos_de_QT"));
        action_A_Propos_de_Taquin = new QAction(MainWindow);
        action_A_Propos_de_Taquin->setObjectName(QString::fromUtf8("action_A_Propos_de_Taquin"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 530, 20));
        menuFicher = new QMenu(menubar);
        menuFicher->setObjectName(QString::fromUtf8("menuFicher"));
        menuFond = new QMenu(menubar);
        menuFond->setObjectName(QString::fromUtf8("menuFond"));
        menuaide = new QMenu(menubar);
        menuaide->setObjectName(QString::fromUtf8("menuaide"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        menuaide->setFont(font);
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFicher->menuAction());
        menubar->addAction(menuFond->menuAction());
        menubar->addAction(menuaide->menuAction());
        menuFicher->addAction(_nouvpartie);
        menuFicher->addAction(_chargpart);
        menuFicher->addAction(_sauvpart);
        menuFicher->addSeparator();
        menuFicher->addAction(_quitpart);
        menuFond->addAction(_imgor);
        menuFond->addAction(_imgfo);
        menuFond->addAction(_imgarb);
        menuFond->addAction(_imgre);
        menuaide->addAction(action_A_propos_de_QT);
        menuaide->addAction(action_A_Propos_de_Taquin);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Taquin ", nullptr));
        _nouvpartie->setText(QCoreApplication::translate("MainWindow", "Nouvelle partie", nullptr));
        _chargpart->setText(QCoreApplication::translate("MainWindow", "Charger", nullptr));
        _quitpart->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
        _sauvpart->setText(QCoreApplication::translate("MainWindow", "Sauvegarder", nullptr));
        _imgor->setText(QCoreApplication::translate("MainWindow", "Orginal", nullptr));
        _imgfo->setText(QCoreApplication::translate("MainWindow", "Foret", nullptr));
        _imgarb->setText(QCoreApplication::translate("MainWindow", "Arbre", nullptr));
        _imgre->setText(QCoreApplication::translate("MainWindow", "R\303\251seau", nullptr));
        action_A_propos_de_QT->setText(QCoreApplication::translate("MainWindow", "A propos de Qt", nullptr));
#if QT_CONFIG(tooltip)
        action_A_propos_de_QT->setToolTip(QCoreApplication::translate("MainWindow", "A propos de Qt", nullptr));
#endif // QT_CONFIG(tooltip)
        action_A_Propos_de_Taquin->setText(QCoreApplication::translate("MainWindow", "A propos de Taquin", nullptr));
#if QT_CONFIG(tooltip)
        action_A_Propos_de_Taquin->setToolTip(QCoreApplication::translate("MainWindow", "A propos de Taquin", nullptr));
#endif // QT_CONFIG(tooltip)
        menuFicher->setTitle(QCoreApplication::translate("MainWindow", "Fichier", nullptr));
        menuFond->setTitle(QCoreApplication::translate("MainWindow", "Fond", nullptr));
        menuaide->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
