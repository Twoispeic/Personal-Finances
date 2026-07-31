#include "sidebarwidget.h"
#include "ui_sidebarwidget.h"
#include <QVBoxLayout>
#include <QPushButton>

SidebarWidget::SidebarWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SidebarWidget)
{
    ui->setupUi(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(4);
    layout->setContentsMargins(8, 16, 8, 16);

    QPushButton* nutTrangChu = new QPushButton("Trang chủ", this);
    QPushButton* nutChiTieu  = new QPushButton("Quản lý chi tiêu", this);
    QPushButton* nutThuNhap  = new QPushButton("Thu nhập cá nhân", this);
    QPushButton* nutMucTieu  = new QPushButton("Mục tiêu tài chính", this);

    for (QPushButton* nut : {nutTrangChu, nutChiTieu, nutThuNhap, nutMucTieu}) {
        nut->setCheckable(true);
        nut->setMinimumHeight(40);
        layout->addWidget(nut);
    }
    layout->addStretch();
    setLayout(layout);

    nutTrangChu->setChecked(true);   // mặc định mở Trang chủ khi khởi động app

    connect(nutTrangChu, &QPushButton::clicked, this, &SidebarWidget::onNutTrangChuClicked);
    connect(nutChiTieu,  &QPushButton::clicked, this, &SidebarWidget::onNutChiTieuClicked);
    connect(nutThuNhap,  &QPushButton::clicked, this, &SidebarWidget::onNutThuNhapClicked);
    connect(nutMucTieu,  &QPushButton::clicked, this, &SidebarWidget::onNutMucTieuClicked);
}

SidebarWidget::~SidebarWidget() {
    delete ui;
}

void SidebarWidget::onNutTrangChuClicked() { emit trangDuocChon(0); }
void SidebarWidget::onNutChiTieuClicked()  { emit trangDuocChon(1); }
void SidebarWidget::onNutThuNhapClicked()  { emit trangDuocChon(2); }
void SidebarWidget::onNutMucTieuClicked()  { emit trangDuocChon(3); }