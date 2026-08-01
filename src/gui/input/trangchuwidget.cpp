#include "trangchuwidget.h"
#include "ui_trangchuwidget.h"
#include "bieudowidget.h" // Gọi thư viện BieuDoWidget vào để sử dụng
#include <QDebug>         // Dùng để in log kiểm tra lúc chạy

TrangChuWidget::TrangChuWidget(QWidget *parent)
    : QWidget(parent)
    , bieuDoThuNho(nullptr)      // đưa lên trước
    , ui(new Ui::TrangChuWidget) // đưa xuống sau
{
    ui->setupUi(this);
    bieuDoThuNho = new BieuDoWidget(this);
}

TrangChuWidget::~TrangChuWidget()
{
    // Dọn dẹp RAM khi đóng widget
    delete ui;
}

void TrangChuWidget::capNhatTongQuan(NguoiDung* nd)
{
    if (nd == nullptr) {
        qDebug() << "Chưa có dữ liệu người dùng!";
        return;
    }
   // ui->lblTongTien->setText(QString::number(nd->tinhTongThuNhap()));
    qDebug() << "Đang cập nhật tổng quan giao diện...";
}

void TrangChuWidget::onKetThucThangClicked()
{
    // TODO: Viết code tính toán, lưu dữ liệu vào database khi hết tháng
    qDebug() << "Nút kết thúc tháng đã được bấm!";

    // Sau khi tính toán xong, phát tín hiệu (signal) để báo cho các widget khác biết dữ liệu đã đổi
    emit duLieuThayDoi();
}