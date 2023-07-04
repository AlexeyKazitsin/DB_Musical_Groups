#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "navigation.h"
#include "labelinfo.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnLgn_clicked()
{
    QString logins = ui->leLgn->text();
    QString passs = ui->lePswd->text();
    if (logins=="alexey" && passs=="1"){
        this->accept();
        Navigation * n = new Navigation(this);
        n->show();
    } else if(logins=="label" && passs=="1"){
        this->accept();
        Labelinfo * li = new Labelinfo(this);
        li->show();
    }else {
        QMessageBox msgBox;
        msgBox.setText("Неправильный пароль или логин!");
        msgBox.exec();
    }
}

