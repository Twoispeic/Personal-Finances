#include "taomuctieudialog.h"
#include "ui_taomuctieudialog.h"
#include <QDebug>

TaoMucTieuDialog::TaoMucTieuDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TaoMucTieuDialog)
{
    ui->setupUi(this);

    // Gán giá trị mặc định lúc mới mở form
    dangONganHan = true;
}

TaoMucTieuDialog::~TaoMucTieuDialog()
{
    delete ui;
}

bool TaoMucTieuDialog::laNganHan() const {
    return dangONganHan;
}

QString TaoMucTieuDialog::layTen() const {
    // TODO: Lấy chữ từ ô nhập liệu, vd: return ui->txtTenMucTieu->text();
    return QString("");
}

double TaoMucTieuDialog::laySoTienMucTieu() const {
    return 0.0; // TODO: return ui->spinSoTien->value();
}

int TaoMucTieuDialog::layThoiHanThang() const {
    return 0; // TODO: Lấy từ ô nhập thời hạn
}

int TaoMucTieuDialog::laySoKyTraGop() const {
    return 0; // TODO: Lấy số kỳ trả góp
}

double TaoMucTieuDialog::laySoTienMoiKy() const {
    return 0.0; // TODO: Lấy số tiền mỗi kỳ
}