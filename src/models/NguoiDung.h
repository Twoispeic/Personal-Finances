#ifndef NGUOIDUNG_H
#define NGUOIDUNG_H

#include <QString>
#include <QList>
#include "ThuNhap.h"
#include "ChiTieu.h"
#include "goals/MucTieu.h"

class NguoiDung {
private:
    QString ten;
    QString congViec;
    QList<ThuNhap> danhSachThuNhap;
    QList<ChiTieu> danhSachChiTieu;
    QList<MucTieu*> danhSachMucTieu;

public:
    NguoiDung();
    NguoiDung(QString ten, QString congViec);


    QString getTen() const;
    void setTen(const QString &ten);

    QString getCongViec() const;
    void setCongViec(const QString &congViec);

    //UML
    void themThuNhap(const ThuNhap &thuNhap);
    void themChiTieu(const ChiTieu &chiTieu);
    MucTieu* taoMucTieuNganHan(const QString& ten, double soTienMucTieu, int thoiHanThang);
    MucTieu* taoMucTieuDaiHan(const QString& ten, double soTienMucTieu, int soKyTraGop, double soTienMoiKy);

    double tinhTongThuNhap() const;
    double tinhTongChiTieu() const;
    double tinhSoDuThang() const;
    // tự tính từ soDuThang, không cần tham số vì đã có sẵn 2 hàm tính tổng
    void phanBoTienTietKiem();
};

#endif // NGUOIDUNG_H