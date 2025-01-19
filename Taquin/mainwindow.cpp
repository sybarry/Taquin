#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),_saisie(this)
    , ui(new Ui::MainWindow),
      _button_nouv(nullptr),_button_sauv(nullptr),
      _button_charg(nullptr),_texte(new QLabel()),_tuiles(),_statutpartie(partie::terminer),_nbcoup(0),_positions(),_taille(3)
{

    ui->setupUi(this);
    this->setWindowIcon(QIcon("/home/barry/Bureau/test/Taquin/Taquin/Images/240px-15-puzzle.png"));
    ui->menuaide->setTitle("");
    ui->menuaide->setIcon(style()->standardIcon(QStyle::SP_DialogHelpButton));
    ui->action_A_Propos_de_Taquin->setIcon(style()->standardIcon(QStyle::SP_FileDialogInfoView));
    ui->action_A_propos_de_QT->setIcon(style()->standardIcon(QStyle::SP_FileDialogInfoView));
    ui->_nouvpartie->setShortcut(QKeySequence::New);
    ui->_quitpart->setShortcut(QKeySequence("CTRL+Q"));
    ui->_sauvpart->setShortcut(QKeySequence::Save);
    ui->_chargpart->setShortcut(QKeySequence::Open);

    _button_nouv=new QPushButton(this);
    _button_sauv=new QPushButton(this);
    _button_charg=new QPushButton(this);
    _button_nouv->setText(tr("Nouvelle partie"));
    _button_sauv->setText(tr("Sauvégarde une partie"));
    _button_charg->setText(tr("Charger une partie"));
    _texte->setText(QString("%1%2").arg(tr("Nombre de coups : ")).arg(_nbcoup));
    _texte->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    connect(_button_nouv,&QPushButton::clicked,this,&MainWindow::nouvellepartie);

    //layout central ou seront placer la grille et le QVBOXLAYOUT qui contient des button
    QWidget* wid= new QWidget(this);
    QHBoxLayout* layoutcentral= new QHBoxLayout();

    //definition de la grille
    QGridLayout* grille=new QGridLayout();
    //permet d'afficher compt dans chaque Qpushbutton ajouté à la grille
    int compt=0;
    //creation et ajout des Qpushbutton dans la grille
    for(int i=0;i<3;++i){
        vector<int>tab1;
        for(int j=0;j<3;++j){
            QPushButton*  tuile=new QPushButton(this);
            tuile->setFixedSize(QSize(100,100));
            if(i==2&&j==2){
                tuile->setDisabled(true);
                tuile->setAccessibleName(QString("%1").arg(-1));
                grille->addWidget(tuile,i,j);
                grille->setHorizontalSpacing(3);
                grille->setVerticalSpacing(3);
                _tuiles.append(tuile);
                tuile->hide();
                tab1.push_back(-1);


            }
            else {
                tuile->setStyleSheet("background-color:blue");
                tuile->setText(QString("%1").arg(compt));
                tuile->setAccessibleName(QString("%1").arg(compt));
                tuile->connect(tuile,&QPushButton::clicked,this,&MainWindow::move);
                grille->addWidget(tuile,i,j);
                grille->setHorizontalSpacing(3);
                grille->setVerticalSpacing(3);
                _tuiles.append(tuile);
                tab1.push_back(compt);

                ++compt;

            }

        }
        _positions.push_back(tab1);
    }
    QVBoxLayout* layout1=new QVBoxLayout();
    layout1->addWidget(_button_nouv,1);
    layout1->addWidget(_button_charg,1);
    layout1->addWidget(_button_sauv,1);
    layout1->addWidget(_texte,1,Qt::AlignTop|Qt::AlignLeft);

    layoutcentral->addLayout(grille,2);
    layoutcentral->addLayout(layout1);
    wid->setLayout(layoutcentral);
    this->setCentralWidget(wid);

    this->adjustSize();
    this->setFixedSize(this->width(),this->height());

//mise en place de toutes les connexions
    connect(this->ui->action_A_propos_de_QT,&QAction::triggered,this,&MainWindow::aproposqt);
    connect(this->ui->action_A_Propos_de_Taquin,&QAction::triggered,this,&MainWindow::aprops);
    connect(ui->_imgarb,&QAction::triggered,this,&MainWindow::charge_image_arbre);
    connect(ui->_imgfo,&QAction::triggered,this,&MainWindow::charge_image_foret);
    connect(ui->_imgre,&QAction::triggered,this,&MainWindow::charge_image_reseau);
    connect(ui->_imgor,&QAction::triggered,this,&MainWindow::charge_image_org);
    connect(this,&MainWindow::emetaction,this,&MainWindow::recoi_action);
    connect(this->ui->_quitpart,&QAction::triggered,this,&MainWindow::quitter);
    connect(this,&MainWindow::quit,this,&QApplication::quit);
    connect(ui->_nouvpartie,&QAction::triggered,this,&MainWindow::nouvellepartie);
    connect(this->_button_sauv,&QPushButton::clicked,this,&MainWindow::sauver_partie);
    connect(this->ui->_sauvpart,&QAction::triggered,this,&MainWindow::sauver_partie);
    connect(this->_button_charg,&QPushButton::clicked,this,&MainWindow::charger_partie);
    connect(ui->_chargpart,&QAction::triggered,this,&MainWindow::charger_partie);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//charge l'image dans la grille
void MainWindow::charger_image(QString image)
{
    if(!image.isEmpty()){
     QPixmap images(image);
     QPixmap img(images.scaled(_taille*100,_taille*100));
       for (int i = 0; i < _taille; ++i)
           for (int j = 0; j < _taille; ++j){
               _tuiles[i*_taille+j]->setStyleSheet("");
                 if(_tuiles[i*_taille+j]->accessibleName().toInt()!=-1){
                    _tuiles[i*_taille+j]->setText("");
                    QIcon ico(img.copy(j*100,i*100,100,100));
                    _tuiles[i*_taille+j]->setIcon(ico);
                    _tuiles[i*_taille+j]->setIconSize(QSize(100,100));
                 }

           }

     }
}


//permet de permuter ou génerer la matrice  pour le jeux
void MainWindow::generermatricejeux()
{
    srand(time(0));
    for (int i = 0; i < _taille; i++) {
        for (int j = 0; j < _taille; j++) {
            int row = rand() % _taille;
            int Col = rand() % _taille;

            int temp = _positions[i][j];
            _positions[i][j] = _positions[row][Col];
            _positions[row][Col] = temp;
        }
    }
}


//retourne la tuile vide
QPushButton* MainWindow::tuilevide() const
{
    for(auto&c: _tuiles)
        if(c->accessibleName().toInt()==-1)
            return c;
    return nullptr;

}

//renvoie les coordonées de la tuile vide
QPoint MainWindow::positiontuilevide() const
{
    int row,cols,_,__;
    if(tuilevide()){
        QWidget*wid=this->centralWidget();
        QHBoxLayout*layout=wid->findChild<QHBoxLayout*>();
        QGridLayout*grille=layout->findChild<QGridLayout*>();
        grille->getItemPosition(grille->indexOf(tuilevide()),&row,&cols,&_,&__);
        return QPoint(row,cols);
    }
    return QPoint(-1,-1);

}

//permet de trier la Qlist des tuiles pour mieux placer les images
void MainWindow::trietuiles()
{
    QList<QPushButton*>temps(_tuiles);
    QPushButton*button=tuilevide();
    _tuiles.clear();

    for(int i=0;i<(_taille*_taille)-1;++i)
        for(auto&c:temps)
            if(c->accessibleName().toInt()==i){
                _tuiles.append(c);
                break;
       }
_tuiles.append(button);
temps.clear();
}

//verife si la partie est gagnée
bool MainWindow::partiegagner() const
{

    if(_positions[_taille-1][_taille-1]!=-1)
        return false;
    else{
        vector<int>trie;
        for(int i=0;i<_taille;++i){
            if(i==_taille-1){
                if(!is_sorted(_positions[i].begin(),_positions[i].end()-1))
                    return false;
                else
                trie.insert(trie.end(),_positions[i].begin(),_positions[i].end()-1);
            }
            else{
                if(!is_sorted(_positions[i].begin(),_positions[i].end()))
                    return false;
                else
                 trie.insert(trie.end(),_positions[i].begin(),_positions[i].end());
            }
        }
             return is_sorted(trie.begin(),trie.end());
    }

}

//genère une matrice de jeu des entiers allant de -1 à la (taille du taquin au carré) -2
void MainWindow::creermatrice()
{     _positions.clear();
      int compt=0;
        for(int i=0;i<_taille;++i){
            vector<int>tab;
            for(int j=0;j<_taille;++j){
                if(i==_taille-1&&j==_taille-1){

                    tab.push_back(-1);
                }
                else {
                    tab.push_back(compt);

                    ++compt;

                }

            }
            _positions.push_back(tab);
        }

}

//modifie ou replace la grille
void MainWindow::modifiegrille()
{

    // Widget central
    QWidget* wid = this->centralWidget();

    // Layout central
    QHBoxLayout* layout = wid->findChild<QHBoxLayout*>();


    // Ancienne QGridlayout se trouvant dans le layout central
    QGridLayout* oldgrille = layout->findChild<QGridLayout*>();


    // Supprimer tous les QPushbutton contenus dans l'ancienne grille qui sont également présents dans l'attribut _tuiles
    for(auto&c:_tuiles)
        c->deleteLater();
    _tuiles.clear();

    //creations de la nouvelle grille
    QGridLayout*grille=new QGridLayout();
    int i=0;
    for (const auto& pos : _positions) {
        int j=0;
        for (const auto& val : pos) {
            QPushButton* button = new QPushButton(this);

            button->setFixedSize(100, 100);
             button->setAccessibleName(QString::number(val));
            button->setDisabled(val == -1);
            if(button->accessibleName().toInt()==-1)
            button->hide();
            grille->addWidget(button,i,j);

            if (val != -1){
                connect(button, &QPushButton::clicked, this, &MainWindow::move);
            }
            _tuiles.append(button);
            ++j;

        }
        ++i;
    }

  //permet de trier la Qlist des pushbutton afin de mieux placer les images plus tard
   trietuiles();

// Suppression de l'ancienne QGridLayout
  layout->removeItem(oldgrille);

   // Ajout de la nouvelle QGridLayout
  layout->insertLayout(0, grille);

     //ajuste la bonne taille de la fenetre de jeu
    this->setFixedHeight(_taille*100+60);
    this->setFixedWidth(_taille*100+250);

    //emet le signal pour charger le dernier fond
    emit emetaction(_dernierimg);
}


void MainWindow::aprops()
{
    QMessageBox infos;
    infos.setIcon(QMessageBox::Icon::NoIcon);
    infos.setIconPixmap(QPixmap("/home/barry/Bureau/test/Taquin/Taquin/Images/240px-15-puzzle.png").scaled(50,50));
    infos.setText(tr("Cette application a été créée par BARRY SAIKOU YAYA pour le projet Qt de L3 Informatique."));
    infos.setWindowTitle(tr("A propos de Taquin "));
    infos.setWindowIcon(QIcon("/home/barry/Bureau/test/Taquin/Taquin/Images/240px-15-puzzle.png"));
    infos.setStandardButtons(QMessageBox::Ok);
    infos.exec();
}

//permet de deplacer les tuile dans le grille en verifiant si la partie est gagnée ou terminée
void MainWindow::move()
{
    // vérifie si la partie est en cours
     if (_statutpartie == partie::encours) {
    // récupère le QPushButton cliqué par l'utilisateur
    auto button = qobject_cast<QPushButton*>(sender());
    int row=-1, col=-1, _, __;
    QWidget*wid=this->centralWidget();
    QHBoxLayout*layout=wid->findChild<QHBoxLayout*>();
    QGridLayout*grille=layout->findChild<QGridLayout*>();

    // récupère la position dans la grille du QPushButton cliqué
    if (grille && button) {
        grille->getItemPosition(grille->indexOf(button),&row,&col,&_,&__);

    // récupère la position de la tuile vide
    QPoint tuileVide = positiontuilevide();
    int row1 = tuileVide.x();
    int col1 = tuileVide.y();

    // vérifie si le QPushButton cliqué peut être déplacé
    if (hypot(row-row1,col-col1)==1) {
        // échange les positions des QPushButton
        auto item = grille->itemAtPosition(row1, col1);
        if(item){
        QPushButton* temps = qobject_cast<QPushButton*>(item->widget());
        grille->removeItem(grille->itemAtPosition(row, col));
        grille->addWidget(temps, row, col);
        grille->removeItem(grille->itemAtPosition(row1, col1));
        grille->addWidget(button, row1, col1);

        // met à jour le modèle de jeu ou la matrice du jeu
        _positions[row1][col1] = button->accessibleName().toInt();;
        _positions[row][col] = -1;
        ++_nbcoup;

        // affiche le nombre de coups à l'utilisateur
        _texte->setText(QString("%1%2").arg(_nbcoup>1?tr("Nombre de coups : "):tr("Nombre de coups : ")).arg(_nbcoup));
          _button_sauv->setDisabled(false);

        // vérifie si la partie est gagnée
        if (partiegagner()) {
            QMessageBox::information(this, "Fin !", QString("%1%2%3").arg(tr("Félicitations Vous avez gagné ! ")).arg(_nbcoup).arg(tr(" coups !")));
            _statutpartie=partie::terminer;
            }
         }
       }
      }
    }
}
//permet de commencer une nouvelle partie
void MainWindow::nouvellepartie()
{
    int reply = 1;

    if (_statutpartie == partie::encours) {
         QMessageBox msgBox(QMessageBox::Question,tr("Commencer une nouvelle partie!"),tr("Abandonner Cette partie"),QMessageBox::Ok|QMessageBox::Cancel,this);
         QAbstractButton* okButton = msgBox.button(QMessageBox::Ok);
         QAbstractButton* cancelButton = msgBox.button(QMessageBox::Cancel);
         okButton->setText(tr("Oui"));
         cancelButton->setText(tr("Non"));
         reply=msgBox.exec();

    }

    if ((reply == QMessageBox::Ok && _statutpartie == partie::encours) || _statutpartie == partie::terminer) {
        if (_saisie.exec() == QDialog::Accepted) {
            _nbcoup=0;
            // affiche le nombre de coups à l'utilisateur
            _texte->setText(QString("%1%2").arg(_nbcoup>1?tr("Nombre de coups : "):tr("Nombre de coups : ")).arg(_nbcoup));
            _button_sauv->setDisabled(false);

            if(_taille!=_saisie.gettaille()){
                // Obtenir la nouvelle taille de la grille saisie par un QDialog
                _taille=_saisie.gettaille();
                // Générer un tableau à deux dimensions d'entiers
            creermatrice();
            }

            // Permuter la matrice
            generermatricejeux();

            //modifie la grille
            modifiegrille();

          //la partie peut commencer
           _statutpartie=partie::encours;
        }
    }
}


void MainWindow::charge_image_arbre()
{
    charger_image("/home/barry/Bureau/test/Taquin/Taquin/Images/arbre-papillons.jpg");
    _dernierimg="/home/barry/Bureau/test/Taquin/Taquin/Images/arbre-papillons.jpg";
}

void MainWindow::charge_image_reseau()
{
    charger_image("/home/barry/Bureau/test/Taquin/Taquin/Images/reseau-informatique.jpeg");
    _dernierimg="/home/barry/Bureau/test/Taquin/Taquin/Images/reseau-informatique.jpeg";
}

void MainWindow::charge_image_foret()
{
    charger_image("/home/barry/Bureau/test/Taquin/Taquin/Images/saikou.jpg");
    _dernierimg="/home/barry/Bureau/test/Taquin/Taquin/Images/saikou.jpg";
}

void MainWindow::charge_image_org()
{
_dernierimg="";

                  for(auto&button:_tuiles){
                           button->setStyleSheet(button->accessibleName().toInt() == -1 ? "" : "background-color: blue");
                         button->setIcon(QIcon(""));
                         button->setFixedSize(100,100);
                         button->setText(button->accessibleName().toInt()!=-1 ?button->accessibleName():"");

                      }

}

void MainWindow::quitter()
{    int reply = 1;

     if (_statutpartie == partie::encours) {
         QMessageBox msgBox(QMessageBox::Question, tr("Quitter le jeu !"), tr("Abandonner la partie et quitter l'application ?"),QMessageBox::Ok|QMessageBox::Cancel,this);
                QAbstractButton* okButton = msgBox.button(QMessageBox::Ok);
                QAbstractButton* cancelButton = msgBox.button(QMessageBox::Cancel);
                okButton->setText(tr("Oui"));
                cancelButton->setText(tr("Non"));
                reply=msgBox.exec();
         if(reply==QMessageBox::Ok)
             emit quit();
     }
   else
      emit quit();

}

void MainWindow::recoi_action(QString&a)
{
    if(!a.isEmpty()){
        charger_image(a);
    }
    else
        charge_image_org();

}

void MainWindow::sauver_partie()
{
    if(_statutpartie==partie::terminer){
        QMessageBox::information(this,tr("Sauvegarder la partie"),tr("Veuillez démarrer ou charger une partie pour pouvoir sauvegarder!"));
    }
    else{

   // Afficher une boîte de dialogue pour sélectionner le fichier de destination
     QFileDialog dialog(this);
     dialog.setOption(QFileDialog::DontUseNativeDialog);
     dialog.setLabelText(QFileDialog::Accept,tr("Sauvegarder"));
     dialog.setLabelText(QFileDialog::Reject,tr("Annuler"));
      QString  filePath = dialog.getSaveFileName(this, tr("Sauvegarder la partie"), "/home/barry/Bureau/test/Taquin/Taquin/Sauvegarder", "*.save");
    if (!filePath.isNull()) {
        filePath=filePath.endsWith(".save",Qt::CaseInsensitive)?filePath:filePath.append(".save");
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly| QIODevice::Text)) {
            QTextStream out(&file);
            out<<_taille<<" "<<_nbcoup<<"\n";
            for(auto &c:_positions){
                for(auto t:c)
            out <<t<<" ";
            out<<"\n";
            }
            file.close();
            QFileInfo info(filePath);
            QString nomficher(tr("Félicitations, la partie a été enregistrée dans le fichier: ")) ;
                 nomficher.append(info.fileName());
                 nomficher.append(" !");
            QMessageBox::information(this,tr("Partie sauvegardée !"),nomficher);
        }

    }else {
            QMessageBox::warning(this, tr("Attention partie non sauvegardé!"), tr("La partie n'a pas été enregistrée car vous avez annulé la sauvegarde."));
        }


}
}
void MainWindow::charger_partie()
{
    int reply = 1;

    if (_statutpartie == partie::encours) {
         QMessageBox msgBox(QMessageBox::Question,tr("Charger une partie !"), tr("Si vous chargez une partie, vous perdez la partie en cours, voulez-vous charger un jeu?"),QMessageBox::Ok|QMessageBox::Cancel,this);
                QAbstractButton* okButton = msgBox.button(QMessageBox::Ok);
                QAbstractButton* cancelButton = msgBox.button(QMessageBox::Cancel);
                okButton->setText(tr("Oui"));
                cancelButton->setText(tr("Non"));
                reply=msgBox.exec();

    }

    if ((reply == QMessageBox::Ok && _statutpartie == partie::encours) || _statutpartie == partie::terminer) {
        QFileDialog dialog(this);
        dialog.setLabelText(QFileDialog::Accept,tr("Sauvegarder"));
        dialog.setLabelText(QFileDialog::Reject,tr("Annuler"));
         QString filePath = dialog.getOpenFileName(this, tr("Charger partie"), "/home/barry/Bureau/test/Taquin/Taquin/Sauvegarder", "*.save");
        if (!filePath.isNull()) {
            QFile file(filePath);

            if (file.open(QIODevice::ReadOnly| QIODevice::Text)) {
                QTextStream in(&file);
                bool verifie=false;
                int nbcoup=0,taille=-1;
                vector<vector<int>>tab1;
                 set<int>ens;
                while (!in.atEnd()) {
                       QString line = in.readLine().trimmed();
                       QStringList strList = line.split(" ");
                       std::vector<int> tab;
                       for (const QString& s : strList)
                           tab.push_back(s.toInt());

                           if(tab.size()==2){
                            taille=tab[0];
                            nbcoup=tab[1];
                           }
                           else{

                            tab1.push_back(tab);
                            for(auto&c:tab)
                                if((c>=-1) && (c<(taille*taille)-1))//permet de verifier les doublons et le numéro de la tuile ainsi que la tuile vide
                                ens.insert(c);
                           }
                           verifie=(tab.size()==2||tab.size()==taille)?true:false;
                           if(!verifie)
                               break;

            }
           file.close();

//verifier si ficher importé est correct
if(verifie&&ens.size()==taille*taille){
    ens.clear();
    _taille=taille;
    _nbcoup=nbcoup;
    _saisie.settaille(_taille);
    _positions=tab1;
    tab1.clear();

           // affiche le nombre de coups à l'utilisateur
           _texte->setText(QString("%1%2").arg(_nbcoup>1?tr("Nombre de coups : "):tr("Nombre de coups : ")).arg(_nbcoup));

             //modifie la grille
            modifiegrille();

            //verouiller le button de sauvegarde si tuile pas bougé
            _button_sauv->setDisabled(true);

           //la partie peut commencer
            _statutpartie=partie::encours;

      }
else
    QMessageBox::warning(this, tr("Impossible de charger le jeu!"), tr("Impossible de charger le jeu, fichier corrompu"));
     }

  }
}

}

void MainWindow::aproposqt()
{
    string date = __DATE__;
       QString annee (QString().fromStdString(date.substr(date.length() - 4, 4)));
    QString aboutQtText = QApplication::translate("QDialog", "<h3>A propos de Qt</h3>"
            "<p>This program uses Qt version %1.</p>"
             "<p>Qt provides single-source portability across all major desktop operating systems. It is also available for embedded Linux and other embedded and mobile operating systems.</p>"
             "<p>Qt is available under multiple licensing options designed to accommodate the needs of various users.</p>"
             "<p>Qt licensed under our commercial licence agreement is appropriate for development of <br> proprietary/commercial software where you do "
              "not want to share any source code with  third parties or otherwise cannot comply with terms of GNU (L)GPL.</p>"
             "<p>Qt licensed under GNU (L)GPL is appropriate for the development of Qt applications"
              " provided you can comply with the terms and conditions of the respective licences</p>"
            "<p>Please see <a href='https://www.qt.io/licensing'>qt.io/licensing</a> for an overview of Qt licensing.</p>"
             "<p>Copyright (C) 2008-%2 The Qt Company Ltd and other contributors. </p>"
              "<p>Qt and Qt logo are trademarks of The Qt Company Ltd.</p>"
            "<p>Qt is The Qt Company Ltd product developed as an open source project. See <a href='https://www.qt.io'>qt.io</a> for more information.</p>").arg(qVersion()).arg(annee);

        QMessageBox *dialog=new QMessageBox(QMessageBox::NoIcon,tr("A propos de Qt"),"",QMessageBox::NoButton,this);
        dialog->setIconPixmap(QPixmap("/home/barry/Bureau/test/Taquin/Taquin/Images/qtinfos.png").scaled(60,60));
        dialog->setText(aboutQtText);
        dialog->setTextFormat(Qt::AutoText);
        dialog->adjustSize();

        dialog->exec();

}
