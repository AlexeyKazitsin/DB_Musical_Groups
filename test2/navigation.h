#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QDialog>

namespace Ui {
class Navigation;
}

class Navigation : public QDialog
{
    Q_OBJECT

public:
    explicit Navigation(QWidget *parent = nullptr);
    ~Navigation();

private slots:
    void on_btnOpenMembers_clicked();

    void on_btnOpenGroups_clicked();

    void on_btnOpenAlbums_clicked();

    void on_btnOpenPlaces_clicked();

    void on_btnOpenTours_clicked();

    void on_btnOpenSongs_clicked();

private:
    Ui::Navigation *ui;
};

#endif // NAVIGATION_H
