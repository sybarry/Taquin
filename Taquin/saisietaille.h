#ifndef SAISIETAILLE_H
#define SAISIETAILLE_H
#include <QDialog>
#include<QStyle>

namespace Ui {
class saisietaille;
}

class saisietaille : public QDialog
{
    Q_OBJECT

public:
    explicit saisietaille(QWidget *parent = nullptr);
    ~saisietaille();
    int gettaille() const;
    void settaille(int a);

signals:
    void sizechanged();
private:
    Ui::saisietaille *ui;
};

#endif // SAISIETAILLE_H
