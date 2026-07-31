#include "thunhapcanhanwidget.h"
#include "ui_thunhapcanhanwidget.h"
#include <QDebug> // Thêm thư viện để in log

ThuNhapCaNhanWidget::ThuNhapCaNhanWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::thunhapcanhanwidget)
{
    ui->setupUi(this);

    // TODO: Kết nối nút bấm lưu thu nhập trên giao diện với hàm xử lý
    // connect(ui->btnLuuThuNhap, &QPushButton::clicked, this, &ThuNhapCaNhanWidget::onLuuThuNhapClicked);
}

ThuNhapCaNhanWidget::~ThuNhapCaNhanWidget()
{
    delete ui;
}

void ThuNhapCaNhanWidget::hienThiSoTienThangHienTai(double soTien)
{
    // TODO: Gắn số tiền lên Label trên giao diện
    // ui->lblSoTien->setText(QString::number(soTien));
    qDebug() << "Đang hiển thị thu nhập tháng hiện tại:" << soTien;
}

void ThuNhapCaNhanWidget::onLuuThuNhapClicked()
{
    // TODO: Lấy dữ liệu từ ô nhập, lưu vào Database
    qDebug() << "Đã bấm nút Lưu thu nhập!";

    // Phát tín hiệu báo cho các màn hình khác biết dữ liệu đã thay đổi
    emit duLieuThayDoi();
}