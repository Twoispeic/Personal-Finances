#include "bieudowidget.h"
#include "ui_bieudowidget.h"

#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

BieuDoWidget::BieuDoWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BieuDoWidget)
{
    ui->setupUi(this);
}

BieuDoWidget::~BieuDoWidget() {
    delete ui;
}

void BieuDoWidget::veBieuDoChiTieu(const QMap<LoaiChiTieu, double>& duLieu) {
    QPieSeries* series = new QPieSeries();
    series->setHoleSize(0.6);   // tạo lỗ giữa -> biểu đồ dạng donut giống mockup

    struct ThongTinLoai { QString ten; QString mau; };
    QMap<LoaiChiTieu, ThongTinLoai> thongTin = {
        { TIEN_SINH_HOAT, {"Tiền sinh hoạt", "#6FE3B4"} },
        { TIEN_DIEN_NUOC, {"Tiền điện nước", "#5B9BFF"} },
        { TIEN_NHA,       {"Tiền nhà",       "#FF8C6B"} },
        { KHAC,           {"Khác",           "#A78BFA"} }
    };

    for (auto it = duLieu.constBegin(); it != duLieu.constEnd(); ++it) {
        if (it.value() <= 0) continue;   // bỏ qua danh mục chưa chi gì, tránh lát cắt 0%

        QPieSlice* slice = series->append(thongTin[it.key()].ten, it.value());
        slice->setColor(QColor(thongTin[it.key()].mau));
        slice->setLabelVisible(false);   // ẩn label trên chart, đã có chú thích riêng bên cạnh (theo mockup)
        slice->setBorderWidth(0);
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();             // ẩn legend mặc định, tự làm chú thích riêng bằng QLabel
    chart->setBackgroundVisible(false);  // trong suốt, hiện màu nền QSS phía sau
    chart->setMargins(QMargins(0, 0, 0, 0));

    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
    ui->chartView->setStyleSheet("background: transparent;");
}