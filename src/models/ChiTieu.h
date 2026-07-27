#ifndef CHITIEU_H
#define CHITIEU_H

#include <QDate>

enum LoaiChiTieu {
    DIEN_NUOC_WIFI,
    TRO_AN_UONG,
    KHAC
};

class ChiTieu {
private:
    LoaiChiTieu loai;
    double soTien;
    QDate ngay;

public:
    ChiTieu();
    ChiTieu(LoaiChiTieu loai, double soTien, QDate ngay);

    double getSoTien() const;
    LoaiChiTieu getLoai() const;
    QDate getNgay() const;
};

#endif // CHITIEU_H