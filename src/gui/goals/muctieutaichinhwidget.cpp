#include "muctieutaichinhwidget.h"
#include "ui_muctieutaichinhwidget.h"
#include "taomuctieudialog.h"   // Gọi popup thêm mục tiêu
#include "muctieucardwidget.h"  // Gọi thẻ mục tiêu thu nhỏ
#include <QDebug>

MucTieuTaiChinhWidget::MucTieuTaiChinhWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MucTieuTaiChinhWidget)
{
    ui->setupUi(this);

    // Lưu ý: Nếu trên file .ui bạn chưa thả sẵn Layout, bạn sẽ phải new nó ở đây
    // layoutNganHan = new QVBoxLayout(ui->widgetNganHan);
    // layoutDaiHan = new QVBoxLayout(ui->widgetDaiHan);

    // TODO: Kết nối nút "Thêm Mục Tiêu"
    // connect(ui->btnThemMucTieu, &QPushButton::clicked, this, &MucTieuTaiChinhWidget::onThemMucTieuClicked);
}

MucTieuTaiChinhWidget::~MucTieuTaiChinhWidget()
{
    delete ui;
}

void MucTieuTaiChinhWidget::taiLaiDanhSach(NguoiDung* nd)
{
    if (!nd) return; // Kiểm tra an toàn

    qDebug() << "Đang tải lại danh sách mục tiêu...";
    capNhatOTong(nd);

    // TODO: Xóa các thẻ cũ trong layout, đọc danh sách từ 'nd' và tạo MucTieuCardWidget mới nhét vào layout
}

void MucTieuTaiChinhWidget::capNhatOTong(NguoiDung* nd)
{
    qDebug() << "Cập nhật con số tổng tiền...";
    // TODO: Tính toán và hiển thị lên giao diện
}

void MucTieuTaiChinhWidget::onThemMucTieuClicked()
{
    qDebug() << "Đang mở cửa sổ tạo mục tiêu mới!";

    /* Mẫu code gọi popup sau này:
    TaoMucTieuDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        // Xử lý lưu và cập nhật giao diện
        emit duLieuThayDoi();
    }
    */
}