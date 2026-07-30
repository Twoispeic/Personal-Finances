#include "quanlychitieuwidget.h"
#include "ui_quanlychitieuwidget.h"
#include <QDebug>

QuanLyChiTieuWidget::QuanLyChiTieuWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::quanlychitieuwidget)
{
    ui->setupUi(this);

    // TODO: Kết nối sự kiện nút bấm và bộ lọc
    // connect(ui->btnThemChiTieu, &QPushButton::clicked, this, &QuanLyChiTieuWidget::onThemChiTieuClicked);
    // connect(ui->cboLocChiTieu, &QComboBox::currentIndexChanged, this, &QuanLyChiTieuWidget::onLocThayDoi);
}

QuanLyChiTieuWidget::~QuanLyChiTieuWidget()
{
    delete ui;
}

void QuanLyChiTieuWidget::taiLaiDanhSach()
{
    // TODO: Xóa danh sách cũ trên giao diện và tải lại từ Database
    qDebug() << "Đang tải lại danh sách chi tiêu...";
}

void QuanLyChiTieuWidget::onThemChiTieuClicked()
{
    // TODO: Mở cái popup (dialog) thêm chi tiêu lên
    // themchitieudialog *dialog = new themchitieudialog(this);
    // dialog->show();
    qDebug() << "Mở cửa sổ Thêm chi tiêu!";
}

void QuanLyChiTieuWidget::onLocThayDoi()
{
    // TODO: Lấy điều kiện lọc hiện tại và cập nhật lại danh sách
    qDebug() << "Bộ lọc vừa bị thay đổi, đang cập nhật lại danh sách...";
}