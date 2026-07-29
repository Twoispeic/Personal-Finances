#include "GopTietKiemDialog.h"

GopTietKiemDialog::GopTietKiemDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Góp Tiết Kiệm");
    setFixedSize(300, 150);

    // Khởi tạo các UI components
    QLabel* label = new QLabel("Nhập số tiền muốn góp:", this);
    spinBoxTien = new QDoubleSpinBox(this);
    spinBoxTien->setMaximum(1000000000); // Set max tuỳ ý
    spinBoxTien->setSuffix(" VNĐ");

    btnXacNhan = new QPushButton("Xác nhận", this);
    btnHuy = new QPushButton("Hủy", this);

    // Layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    buttonLayout->addWidget(btnXacNhan);
    buttonLayout->addWidget(btnHuy);

    mainLayout->addWidget(label);
    mainLayout->addWidget(spinBoxTien);
    mainLayout->addLayout(buttonLayout);

    // Bắt sự kiện click nút
    connect(btnXacNhan, &QPushButton::clicked, this, &QDialog::accept);
    connect(btnHuy, &QPushButton::clicked, this, &QDialog::reject);
}

double GopTietKiemDialog::laySoTienGop() {
    return spinBoxTien->value();
}