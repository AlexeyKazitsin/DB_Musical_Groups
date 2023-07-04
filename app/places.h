#ifndef PLACES_H
#define PLACES_H

#include <QMainWindow>
#include <QSqlDatabase>



namespace Ui { class Places; }


class Places : public QMainWindow
{
    Q_OBJECT

public:
    Places(QWidget *parent = nullptr);
    ~Places();

public slots:
    void dbconnect();
    void selectAll();
    void add();
    void del();

private:
    Ui::Places *ui;
    QSqlDatabase dbconn;
};
#endif // MAINWINDOW_H
