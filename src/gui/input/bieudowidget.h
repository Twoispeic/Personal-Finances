#ifndef BIEUDOWIDGET_H
#define BIEUDOWIDGET_H

#include <QWidget>

namespace Ui {
class bieudowidget;
}

class bieudowidget : public QWidget
{
    Q_OBJECT

public:
    explicit bieudowidget(QWidget *parent = nullptr);
    ~bieudowidget();

private:
    Ui::bieudowidget *ui;
};

#endif // BIEUDOWIDGET_H
