#include "bieudowidget.h"
#include "ui_bieudowidget.h"
#include <QPainter>
#include <QPen>

bieudowidget::bieudowidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::bieudowidget)
{
    ui->setupUi(this);
}

bieudowidget::~bieudowidget()
{
    delete ui;
}

void bieudowidget::paintEvent(QPaintEvent *event)
{
    // Bỏ qua cảnh báo biến event không sử dụng
    Q_UNUSED(event);

    QPainter painter(this);
    // Khử răng cưa giúp nét vẽ vòng tròn mượt mà, không bị vỡ hạt
    painter.setRenderHint(QPainter::Antialiasing);

    // 1. CĂN CHỈNH KÍCH THƯỚC BẢNG VẼ
    // Lấy kích thước nhỏ nhất giữa chiều rộng và chiều cao để vẽ hình tròn không bị méo
    int size = qMin(width(), height()) - 40;
    QRectF rect((width() - size) / 2.0, (height() - size) / 2.0, size, size);

    int penWidth = 20; // Độ dày của viền biểu đồ

    // 2. VẼ VÒNG TRÒN NỀN (TRACK MỜ)
    QPen trackPen(QColor(255, 255, 255, 13)); // Màu trắng trong suốt như HTML
    trackPen.setWidth(penWidth);
    painter.setPen(trackPen);
    painter.drawEllipse(rect);

    // 3. VẼ CÁC CUNG TRÒN CHI TIÊU
    // Lưu ý của Qt: Đơn vị góc là 1/16 độ. (1 độ = 16 đơn vị).
    // 100% = 360 độ. Vậy 1% = 3.6 độ = 57.6 đơn vị Qt.

    // Góc bắt đầu là 90 độ (Góc 12 giờ). Qt vẽ ngược chiều kim đồng hồ, nên muốn vẽ xuôi phải dùng số âm.
    int startAngle = 90 * 16;

    // --- Khoản 1: Tiền ăn (38%) ---
    QPen pen1(QColor("#F2508C")); // Màu hồng
    pen1.setWidth(penWidth);
    pen1.setCapStyle(Qt::RoundCap); // Bo tròn hai đầu nét vẽ
    painter.setPen(pen1);
    int span1 = -(38 * 3.6 * 16);
    painter.drawArc(rect, startAngle, span1);

    // --- Khoản 2: Xăng xe (24%) ---
    startAngle += span1; // Nối tiếp đuôi của cung tròn trước
    QPen pen2(QColor("#FFB35C")); // Màu cam
    pen2.setWidth(penWidth);
    pen2.setCapStyle(Qt::RoundCap);
    painter.setPen(pen2);
    int span2 = -(24 * 3.6 * 16);
    painter.drawArc(rect, startAngle, span2);

    // --- Khoản 3: Tiền nước (16%) ---
    startAngle += span2;
    QPen pen3(QColor("#6E7BFA")); // Màu xanh dương
    pen3.setWidth(penWidth);
    pen3.setCapStyle(Qt::RoundCap);
    painter.setPen(pen3);
    int span3 = -(16 * 3.6 * 16);
    painter.drawArc(rect, startAngle, span3);

    // --- Khoản 4: Khác (22%) ---
    startAngle += span3;
    QPen pen4(QColor("#35DDC0")); // Màu xanh ngọc
    pen4.setWidth(penWidth);
    pen4.setCapStyle(Qt::RoundCap);
    painter.setPen(pen4);
    int span4 = -(22 * 3.6 * 16);
    painter.drawArc(rect, startAngle, span4);

    // 4. VẼ CHỮ Ở GIỮA VÒNG TRÒN
    // Chữ số tổng tiền (5,1tr)
    painter.setPen(QColor("#F4F5FC"));
    QFont fontBig("Segoe UI", 18, QFont::Bold);
    painter.setFont(fontBig);
    painter.drawText(rect, Qt::AlignCenter, "5,1tr\n");

    // Chữ ghi chú (đã chi)
    painter.setPen(QColor("#8A8FC0"));
    QFont fontSmall("Segoe UI", 11);
    painter.setFont(fontSmall);
    // Dịch khung vẽ chữ xuống dưới một chút để không đè lên số
    QRectF textRect = rect.adjusted(0, 36, 0, 0);
    painter.drawText(textRect, Qt::AlignCenter, "đã chi");
}