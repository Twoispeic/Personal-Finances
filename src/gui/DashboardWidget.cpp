#include "dashboardwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QFont>

DashboardWidget::DashboardWidget(QWidget* parent) : QWidget(parent) {
    repoMucTieu.taoBang();
    khoiTaoGiaoDien();
}

void DashboardWidget::khoiTaoGiaoDien() {
    QVBoxLayout* layoutChinh = new QVBoxLayout(this);

    nhanTenNguoiDung = new QLabel("Xin chào!", this);
    QFont fontChao = nhanTenNguoiDung->font();
    fontChao.setPointSize(16);
    fontChao.setBold(true);
    nhanTenNguoiDung->setFont(fontChao);
    layoutChinh->addWidget(nhanTenNguoiDung);

    QHBoxLayout* layoutThe = new QHBoxLayout();

    QFrame* theThuNhap = new QFrame(this);
    theThuNhap->setObjectName("theThuNhap");
    theThuNhap->setStyleSheet("#theThuNhap { background:#eafaf1; border-radius:10px; padding:12px; }");
    QVBoxLayout* layoutTheThuNhap = new QVBoxLayout(theThuNhap);
    layoutTheThuNhap->addWidget(new QLabel("Tổng thu nhập", theThuNhap));
    nhanTongThuNhap = new QLabel("0 đ", theThuNhap);
    nhanTongThuNhap->setStyleSheet("font-size:18px; font-weight:bold; color:#27ae60;");
    layoutTheThuNhap->addWidget(nhanTongThuNhap);

    QFrame* theChiTieu = new QFrame(this);
    theChiTieu->setObjectName("theChiTieu");
    theChiTieu->setStyleSheet("#theChiTieu { background:#fdedec; border-radius:10px; padding:12px; }");
    QVBoxLayout* layoutTheChiTieu = new QVBoxLayout(theChiTieu);
    layoutTheChiTieu->addWidget(new QLabel("Tổng chi tiêu", theChiTieu));
    nhanTongChiTieu = new QLabel("0 đ", theChiTieu);
    nhanTongChiTieu->setStyleSheet("font-size:18px; font-weight:bold; color:#e74c3c;");
    layoutTheChiTieu->addWidget(nhanTongChiTieu);

    QFrame* theSoDu = new QFrame(this);
    theSoDu->setObjectName("theSoDu");
    theSoDu->setStyleSheet("#theSoDu { background:#eaf2fa; border-radius:10px; padding:12px; }");
    QVBoxLayout* layoutTheSoDu = new QVBoxLayout(theSoDu);
    layoutTheSoDu->addWidget(new QLabel("Số dư tháng", theSoDu));
    nhanSoDuThang = new QLabel("0 đ", theSoDu);
    nhanSoDuThang->setStyleSheet("font-size:18px; font-weight:bold;");
    layoutTheSoDu->addWidget(nhanSoDuThang);

    QFrame* theMucTieu = new QFrame(this);
    theMucTieu->setObjectName("theMucTieu");
    theMucTieu->setStyleSheet("#theMucTieu { background:#f5eef8; border-radius:10px; padding:12px; }");
    QVBoxLayout* layoutTheMucTieu = new QVBoxLayout(theMucTieu);
    layoutTheMucTieu->addWidget(new QLabel("Mục tiêu hoàn thành", theMucTieu));
    nhanTienDoMucTieu = new QLabel("0 / 0", theMucTieu);
    nhanTienDoMucTieu->setStyleSheet("font-size:18px; font-weight:bold; color:#8e44ad;");
    layoutTheMucTieu->addWidget(nhanTienDoMucTieu);

    layoutThe->addWidget(theThuNhap);
    layoutThe->addWidget(theChiTieu);
    layoutThe->addWidget(theSoDu);
    layoutThe->addWidget(theMucTieu);

    layoutChinh->addLayout(layoutThe);
    layoutChinh->addStretch();

    setLayout(layoutChinh);
}

void DashboardWidget::capNhatTongQuan(NguoiDung* nguoiDung) {
    if (!nguoiDung) return;

    nhanTenNguoiDung->setText(QString("Xin chào, %1!").arg(nguoiDung->getTen()));

    double tongThu = nguoiDung->tinhTongThuNhap();
    double tongChi = nguoiDung->tinhTongChiTieu();
    double soDu = nguoiDung->tinhSoDuThang();

    nhanTongThuNhap->setText(QString("%1 đ").arg(tongThu, 0, 'f', 0));
    nhanTongChiTieu->setText(QString("%1 đ").arg(tongChi, 0, 'f', 0));
    nhanSoDuThang->setText(QString("%1 đ").arg(soDu, 0, 'f', 0));
    nhanSoDuThang->setStyleSheet(
        QString("font-size:18px; font-weight:bold; color:%1;")
            .arg(soDu >= 0 ? "#27ae60" : "#e74c3c"));

    // Muc tieu doc tu DB (khong tu NguoiDung, vi khong co getter danh sach)
    QList<MucTieu*> danhSachMucTieu = repoMucTieu.layTatCa();
    int soHoanThanh = 0;
    for (MucTieu* mt : danhSachMucTieu)
        if (mt->kiemTraHoanThanh()) ++soHoanThanh;

    nhanTienDoMucTieu->setText(QString("%1 / %2").arg(soHoanThanh).arg(danhSachMucTieu.size()));
    qDeleteAll(danhSachMucTieu); // layTatCa() tao object moi moi lan goi, phai tu giai phong
}
