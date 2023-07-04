#ifndef ALBUMS_H
#define ALBUMS_H

#include <QMainWindow>
#include <QSqlDatabase>



namespace Ui { class Albums; }


class Albums : public QMainWindow
{
    Q_OBJECT

public:
    Albums(QWidget *parent = nullptr);
    ~Albums();

public slots:
    void dbconnect();
    void selectAll();
    void add();
    void del();

private:
    Ui::Albums *ui;
    QSqlDatabase dbconn;
};
#endif // MAINWINDOW_H
