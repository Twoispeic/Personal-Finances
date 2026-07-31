#include "muctieucardwidget.h"
#include "ui_muctieucardwidget.h"
#include <QDebug>

MucTieuCardWidget::MucTieuCardWidget(MucTieu* mt, QWidget *parent)
    : QWidget(parent)
    , mucTieuGanVoi(mt) // Gán dữ liệu vào biến nội bộ
    , ui(new Ui::MucTieuCardWidget)
{
    ui->setupUi(this);

    // TODO: Lấy thông tin từ biến 'mucTieuGanVoi' hiển thị lên label
    // if (mucTieuGanVoi) { ui->lblTen->setText(mucTieuGanVoi->getTen()); }

    // TODO: Kết nối nút Góp tiền
    // connect(ui->btnGopTien, &QPushButton::clicked, this, &MucTieuCardWidget::onGopClicked);
}

MucTieuCardWidget::~MucTieuCardWidget()
{
    delete ui;
}

void MucTieuCardWidget::onGopClicked()
{
    qDebug() << "Nút góp tiền trên card được nhấn!";

    // Bắn tín hiệu ra ngoài để form bự (MucTieuTaiChinhWidget) bắt lấy và xử lý
    if (mucTieuGanVoi) {
        emit yeuCauGopTietKiem(mucTieuGanVoi);
    }
}