#include "navigation.h"
#include "ui_navigation.h"
#include "mainwindow.h"
#include "groups.h"
#include "albums.h"
#include "places.h"
#include "tours.h"
#include "songs.h"

Navigation::Navigation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Navigation)
{
    ui->setupUi(this);
}

Navigation::~Navigation()
{
    delete ui;
}

void Navigation::on_btnOpenMembers_clicked()
{
    MainWindow * w = new MainWindow(this);
    w->show();
}


void Navigation::on_btnOpenGroups_clicked()
{
    Groups * g = new Groups(this);
    g->show();
}


void Navigation::on_btnOpenAlbums_clicked()
{
    Albums * a = new Albums(this);
    a->show();
}


void Navigation::on_btnOpenPlaces_clicked()
{
    Places * pl = new Places(this);
    pl->show();
}


void Navigation::on_btnOpenTours_clicked()
{
    Tours * tour = new Tours(this);
    tour->show();
}


void Navigation::on_btnOpenSongs_clicked()
{
    Songs * song = new Songs(this);
    song->show();
}

