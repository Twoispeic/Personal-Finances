#ifndef THUNHAP_H
#define THUNHAP_H

#include <QString>
#include <QDate>

class ThuNhap {
private:
    QString loai;
    double soTien;
    QDate ngay;

public:
    ThuNhap();
    ThuNhap(QString loai, double soTien, QDate ngay);

    QString getLoai() const;
    void setLoai(const QString &loai);

    double getSoTien() const;
    void setSoTien(double soTien);

    QDate getNgay() const;
    void setNgay(const QDate &ngay);
};

#endif // THUNHAP_H