#include "trangchuwidget.h"
#include "ui_trangchuwidget.h"
#include "bieudowidget.h" // Gọi thư viện BieuDoWidget vào để sử dụng
#include <QDebug>         // Dùng để in log kiểm tra lúc chạy

TrangChuWidget::TrangChuWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::trangchuwidget)
{
    ui->setupUi(this);

    // TODO: Khởi tạo các thành phần giao diện khác nếu cần
    // bieuDoThuNho = new BieuDoWidget(this);

    // TODO: Kết nối nút bấm "Kết thúc tháng" trên file .ui với hàm xử lý
    // connect(ui->btnKetThucThang, &QPushButton::clicked, this, &TrangChuWidget::onKetThucThangClicked);
}

TrangChuWidget::~TrangChuWidget()
{
    // Dọn dẹp RAM khi đóng widget
    delete ui;
}

void TrangChuWidget::capNhatTongQuan(NguoiDung* nd)
{
    // Kiểm tra an toàn: Nếu không có dữ liệu người dùng thì thoát luôn, tránh crash app
    if (nd == nullptr) {
        qDebug() << "Chưa có dữ liệu người dùng!";
        return;
    }

    // TODO: Cập nhật các con số lên giao diện dựa vào dữ liệu của 'nd'
    // Ví dụ: ui->lblTongTien->setText(QString::number(nd->getTongThuNhap()));
    qDebug() << "Đang cập nhật tổng quan giao diện...";
}

void TrangChuWidget::onKetThucThangClicked()
{
    // TODO: Viết code tính toán, lưu dữ liệu vào database khi hết tháng
    qDebug() << "Nút kết thúc tháng đã được bấm!";

    // Sau khi tính toán xong, phát tín hiệu (signal) để báo cho các widget khác biết dữ liệu đã đổi
    emit duLieuThayDoi();
}