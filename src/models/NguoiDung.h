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

    // Getters & Setters
    QString getTen() const;
    void setTen(const QString &ten);

    QString getCongViec() const;
    void setCongViec(const QString &congViec);

    // Nghiệp vụ UML
    void themThuNhap(const ThuNhap &thuNhap);
    void themChiTieu(const ChiTieu &chiTieu);
    MucTieu* taoMucTieu(LoaiMucTieu loai);

    double tinhTongThuNhap() const;
    double tinhTongChiTieu() const;
    double tinhSoDuThang() const;
};

#endif // NGUOIDUNG_H