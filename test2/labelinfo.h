#ifndef LABELINFO_H
#define LABELINFO_H

#include <QMainWindow>

namespace Ui {
class Labelinfo;
}

class Labelinfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit Labelinfo(QWidget *parent = nullptr);
    ~Labelinfo();

private:
    Ui::Labelinfo *ui;
};

#endif // LABELINFO_H
