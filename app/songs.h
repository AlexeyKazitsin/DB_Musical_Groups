#ifndef SONGS_H
#define SONGS_H

#include <QMainWindow>
#include <QSqlDatabase>



namespace Ui { class Songs; }


class Songs : public QMainWindow
{
    Q_OBJECT

public:
    Songs(QWidget *parent = nullptr);
    ~Songs();

public slots:
    void dbconnect();
    void selectAll();
    void add();
    void del();

private:
    Ui::Songs *ui;
    QSqlDatabase dbconn;
};
#endif // MAINWINDOW_H
