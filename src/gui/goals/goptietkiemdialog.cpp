#include "goptietkiemdialog.h"
#include "ui_goptietkiemdialog.h"
#include <QDebug>

GopTietKiemDialog::GopTietKiemDialog(double soTienConDu, MucTieu* mucTieu, QWidget *parent)
    : QDialog(parent)
    , soTienConDu(soTienConDu)       // Gán số tiền dư vào biến nội bộ
    , mucTieuDuocChon(mucTieu)       // Gán mục tiêu vào biến nội bộ
    , ui(new Ui::GopTietKiemDialog)  // Đã được viết thường để tránh lỗi "incomplete type"
{
    ui->setupUi(this);

    // TODO: Hiển thị thông tin lên giao diện lúc mới mở form
    // Ví dụ: ui->lblSoTienConDu->setText(QString::number(soTienConDu));
    // if (mucTieuDuocChon) { ui->lblTenMucTieu->setText(mucTieuDuocChon->layTen()); }
}

GopTietKiemDialog::~GopTietKiemDialog()
{
    delete ui;
}

double GopTietKiemDialog::laySoTienGop() const
{
    // TODO: Lấy số tiền mà người dùng nhập vào ô muốn góp
    // return ui->spinBoxSoTienGop->value();

    qDebug() << "Đang trích xuất số tiền góp từ form...";

    // Tạm thời trả về 0 để không bị lỗi khi biên dịch
    return 0.0;
}