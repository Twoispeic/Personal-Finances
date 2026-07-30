#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QWidget>
#include <QLabel>

#include "models/NguoiDung.h"
#include "database/MucTieuRepository.h"

/*
 * DashboardWidget - man hinh tong quan tai chinh.
 *
 * Ghi chu quan trong: NguoiDung khong co getter danh sach MucTieu, nen so
 * lieu "muc tieu hoan thanh / tong" duoc lay qua MucTieuRepository::layTatCa()
 * (doc tu SQLite), khong lay tu doi tuong NguoiDung dang truyen vao.
 */
class DashboardWidget : public QWidget {
    Q_OBJECT

public:
    explicit DashboardWidget(QWidget* parent = nullptr);

    void capNhatTongQuan(NguoiDung* nguoiDung);

private:
    MucTieuRepository repoMucTieu;

    QLabel* nhanTenNguoiDung;
    QLabel* nhanTongThuNhap;
    QLabel* nhanTongChiTieu;
    QLabel* nhanSoDuThang;
    QLabel* nhanTienDoMucTieu;

    void khoiTaoGiaoDien();
};

#endif // DASHBOARDWIDGET_H
