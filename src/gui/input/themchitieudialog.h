#ifndef THEMCHITIEUDIALOG_H
#define THEMCHITIEUDIALOG_H

#include <QWidget>

namespace Ui {
class themchitieudialog;
}

class themchitieudialog : public QWidget
{
    Q_OBJECT

public:
    explicit themchitieudialog(QWidget *parent = nullptr);
    ~themchitieudialog();

private:
    Ui::themchitieudialog *ui;
};

#endif // THEMCHITIEUDIALOG_H
