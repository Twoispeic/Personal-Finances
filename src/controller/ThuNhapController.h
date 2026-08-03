#ifndef THUNHAPCONTROLLER_H
#define THUNHAPCONTROLLER_H

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include "models/NguoiDung.h"

class ThuNhapController : public QObject {
    Q_OBJECT
    // BỔ SUNG: Dữ liệu vẽ biểu đồ cột (12 tháng gần nhất)
    Q_PROPERTY(QVariantList thongKe12Thang READ thongKe12Thang NOTIFY duLieuThayDoi)

    // BỔ SUNG: Các con số tổng quan cho trang Thu Nhập
    Q_PROPERTY(double tongThuNhap12Thang READ tongThuNhap12Thang NOTIFY duLieuThayDoi)
    Q_PROPERTY(double tongTienTietKiem READ tongTienTietKiem NOTIFY duLieuThayDoi)

public:
    explicit ThuNhapController(NguoiDung* nd, QObject* parent = nullptr);

    QVariantList thongKe12Thang() const;
    double tongThuNhap12Thang() const;
    double tongTienTietKiem() const;

    Q_INVOKABLE void luuThang(double soTien);
    Q_INVOKABLE void taiLai(); // Hàm để làm mới dữ liệu biểu đồ
    Q_INVOKABLE void xoaThangHienTai();//Xoa thang
signals:
    void duLieuThayDoi();

private:
    NguoiDung* nguoiDung;
    QVariantList m_thongKe12Thang;
    double m_tongThuNhap12Thang = 0.0;
    double m_tongTienTietKiem = 0.0;
};

#endif // THUNHAPCONTROLLER_H