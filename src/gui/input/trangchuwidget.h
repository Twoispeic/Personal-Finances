#ifndef BIEUDOWIDGET_H
#define BIEUDOWIDGET_H

#include <QWidget>

namespace Ui {
class BieuDoWidget;
}

class bieudowidget : public QWidget
{
    Q_OBJECT

public:
    explicit bieudowidget(QWidget *parent = nullptr);
    ~bieudowidget();

protected:
    // HÀM ẢO (VIRTUAL FUNCTION): Dùng để tự vẽ biểu đồ (Thỏa mãn tiêu chí OOP)
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::BieuDoWidget *ui;
};

#endif // BIEUDOWIDGET_H