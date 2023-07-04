#ifndef TOURS_H
#define TOURS_H

#include <QMainWindow>
#include <QSqlDatabase>



namespace Ui { class Tours; }


class Tours : public QMainWindow
{
    Q_OBJECT

public:
    Tours(QWidget *parent = nullptr);
    ~Tours();

public slots:
    void dbconnect();
    void selectAll();
    void add();
    void del();

private:
    Ui::Tours *ui;
    QSqlDatabase dbconn;
};
#endif // MAINWINDOW_H
