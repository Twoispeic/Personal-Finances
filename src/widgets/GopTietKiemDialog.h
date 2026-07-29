#ifndef GOPTIETKIEMDIALOG_H
#define GOPTIETKIEMDIALOG_H

#include <QDialog>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class GopTietKiemDialog : public QDialog {
    Q_OBJECT
private:
    QDoubleSpinBox* spinBoxTien;
    QPushButton* btnXacNhan;
    QPushButton* btnHuy;
    double soTienConDu; // Lưu số tiền còn dư theo UML

public:
    explicit GopTietKiemDialog(QWidget *parent = nullptr);
    double laySoTienGop(); // Trả về số tiền nhập vào
};

#endif // GOPTIETKIEMDIALOG_H