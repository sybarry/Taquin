/*
Ceci est le jeu de taquin pour le projet QT de la L3 informatique.
toute la structure du code est contenu dans le ficher mainWindow.h et mainWindow.cpp
le ficher saisietaille.h et saisietaille.cpp ne contient que la boite de dialog pour la saisie de la taille du taquin

*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"saisietaille.h"
#include <QMainWindow>
#include<QtGui>
#include<iostream>
#include<QStyle>
#include<QGridLayout>
#include<QLabel>
#include<QPushButton>
#include<QtWidgets>
#include<QList>
#include<vector>
#include<cstdlib>
#include<ctime>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include<set>
#include <algorithm>
#include<QDesktopServices>
#include <QtCore/QCoreApplication>
#include <QtCore/QDate>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class saisietaille;
enum class partie {terminer,encours};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void charger_image(QString image=" ");//fonction qui permet de charger l'image dans la tuile
    void generermatricejeux();
    QPushButton  *tuilevide() const;
    QPoint positiontuilevide() const;
    void trietuiles();
    bool partiegagner() const;
    void creermatrice();
    void modifiegrille();

 signals:
    void quit();
    void emetaction(QString&a);

 public slots:
void aprops();// evenement information de qt
void move();
void nouvellepartie();
void charge_image_arbre();
void charge_image_reseau();
void charge_image_org();
void charge_image_foret();
void quitter();
void recoi_action(QString&a);
void sauver_partie();
void charger_partie();
void aproposqt();



private:
    Ui::MainWindow *ui;
  saisietaille   _saisie; // widget de saisie de taille

QPushButton * _button_nouv,*_button_sauv,*_button_charg;
QString _dernierimg;//dernier image emit

QLabel * _texte;
QList<QPushButton*>_tuiles;
int _nbcoup, _taille;
vector<vector<int>>_positions;
partie _statutpartie;//pour determiner si partie en cours ou terminers
};
#endif // MAINWINDOW_H
