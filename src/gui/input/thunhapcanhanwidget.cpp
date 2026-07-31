#include "thunhapcanhanwidget.h"
#include "ui_thunhapcanhanwidget.h"
#include <QDebug> // Thêm thư viện để in log

ThuNhapCaNhanWidget::ThuNhapCaNhanWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ThuNhapCaNhanWidget)
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
    bool hopLe;
    double soTien = ui->oNhapSoTien->text().toDouble(&hopLe);   // tên biến ví dụ, cần khớp objectName thật

    if (!hopLe || soTien < 0) {
        qDebug() << "So tien khong hop le!";
        return;
    }

    ThuNhapRepository repo;
    repo.luuThuNhapThang(soTien);   // hàm UPSERT đã viết ở tin trước

    emit duLieuThayDoi();
}