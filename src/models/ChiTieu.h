#ifndef CHITIEU_H
#define CHITIEU_H
#include <QDate>

enum LoaiChiTieu {
    TIEN_SINH_HOAT,
    TIEN_DIEN_NUOC,
    TIEN_NHA,
    KHAC
};

class ChiTieu {
private:
    LoaiChiTieu loai;
    double soTien;
    QDate ngay;
    int id = -1;

public:
    ChiTieu();
    ChiTieu(LoaiChiTieu loai, double soTien, QDate ngay);

    double getSoTien() const;
    LoaiChiTieu getLoai() const;
    QDate getNgay() const;

    void setSoTien(double soTien);
    void setLoai(LoaiChiTieu loai);
    void setNgay(const QDate& ngay);

    int getId() const;
    void datId(int idMoi);
};
#endif // CHITIEU_H