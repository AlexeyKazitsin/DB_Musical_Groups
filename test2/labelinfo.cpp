#include "labelinfo.h"
#include "ui_labelinfo.h"

Labelinfo::Labelinfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Labelinfo)
{
    ui->setupUi(this);
}

Labelinfo::~Labelinfo()
{
    delete ui;
}
