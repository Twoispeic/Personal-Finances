#include "bieudowidget.h"
#include "ui_bieudowidget.h"

BieuDoWidget::BieuDoWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BieuDoWidget)
{
    ui->setupUi(this);
}

bieudowidget::~bieudowidget()
{
    delete ui;
}

cpp
    void BieuDoWidget::veBieuDoChiTieu(const QMap<LoaiChiTieu, double>& duLieu) {
    // TODO: nối vào QChartView thật khi có objectName, tạm thời để trống không lỗi
}