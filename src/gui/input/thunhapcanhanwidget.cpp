#include "thunhapcanhanwidget.h"
#include "ui_thunhapcanhanwidget.h"
#include <QDebug> // Thêm thư viện để in log
#include "database/ThuNhapRepository.h" // (Nhớ sửa lại tên file cho đúng nếu Kha đặt tên khác nhé)

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
   // ui->lblSoTien->setText(QString::number(soTien));   //Tạm thời tắt do chưa có biến lblSoTien
    qDebug() << "Đang hiển thị thu nhập tháng hiện tại:" << soTien;
}

 void ThuNhapCaNhanWidget::onLuuThuNhapClicked()
    {
        // TẠM TẮT TOÀN BỘ LOGIC VÌ GIAO DIỆN CHƯA HOÀN THIỆN
        // bool hopLe;
        // double soTien = ui->oNhapSoTien->text().toDouble(&hopLe);

        // if (!hopLe || soTien < 0) {
        //     qDebug() << "So tien khong hop le!";
        //     return;
        // }

        // ThuNhapRepository repo;
        // repo.luuThuNhapThang(soTien);

        qDebug() << "Đã giả lập bấm nút lưu thu nhập!";

        // Tạm thời cứ phát tín hiệu để các màn hình khác biết
        emit duLieuThayDoi();
    }