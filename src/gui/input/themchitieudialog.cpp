#include "themchitieudialog.h"
#include "ui_themchitieudialog.h"
#include <QDebug>

ThemChiTieuDialog::ThemChiTieuDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ThemChiTieuDialog)
{
    ui->setupUi(this);
}

ThemChiTieuDialog::~ThemChiTieuDialog()
{
    delete ui;
}

ChiTieu ThemChiTieuDialog::layChiTieuMoi() const
{
    // TODO: Lấy dữ liệu thực tế từ các ô nhập liệu (LineEdit, ComboBox, SpinBox...) trên giao diện
    // Ví dụ:
    // QString ten = ui->txtTenChiTieu->text();
    // double soTien = ui->spinBoxSoTien->value();

    qDebug() << "Đang trích xuất dữ liệu chi tiêu mới từ form...";

    // Tạm thời trả về một đối tượng ChiTieu rỗng để trình biên dịch không báo lỗi thiếu return
    return ChiTieu();
}