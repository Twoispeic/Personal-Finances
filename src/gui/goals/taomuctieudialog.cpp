#include "taomuctieudialog.h"
#include "ui_taomuctieudialog.h"

TaoMucTieuDialog::TaoMucTieuDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TaoMucTieuDialog)
{
    ui->setupUi(this);

    dangONganHan = true;   // mặc định mở lên là tab Ngắn hạn (index 0)

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, [this](int index) {
        dangONganHan = (index == 0);
    });
}

TaoMucTieuDialog::~TaoMucTieuDialog() {
    delete ui;
}

bool TaoMucTieuDialog::laNganHan() const {
    return dangONganHan;
}

QString TaoMucTieuDialog::layTen() const {
    return dangONganHan ? ui->txtTenNganHan->text() : ui->txtTenDaiHan->text();
}

double TaoMucTieuDialog::laySoTienMucTieu() const {
    return dangONganHan ? ui->spinSoTienNganHan->value() : ui->spinSoTienDaiHan->value();
}

int TaoMucTieuDialog::layThoiHanThang() const {
    return ui->spinThoiHanThang->value();
}

int TaoMucTieuDialog::laySoKyTraGop() const {
    return ui->spinSoKyTraGop->value();
}
