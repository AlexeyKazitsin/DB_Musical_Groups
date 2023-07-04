#ifndef GROUPS_H
#define GROUPS_H

#include <QMainWindow>
#include <QSqlDatabase>



namespace Ui { class Groups; }


class Groups : public QMainWindow
{
    Q_OBJECT

public:
    Groups(QWidget *parent = nullptr);
    ~Groups();

public slots:
    void dbconnect();
    void selectAll();
    void add();
    void del();

private:
    Ui::Groups *ui;
    QSqlDatabase dbconn;
};
#endif // MAINWINDOW_H
