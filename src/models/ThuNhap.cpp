#include "ThuNhap.h"

ThuNhap::ThuNhap()
    : loai(""), soTien(0.0), ngay(QDate::currentDate()) {}

ThuNhap::ThuNhap(QString loai, double soTien, QDate ngay)
    : loai(loai), soTien(soTien), ngay(ngay) {}

QString ThuNhap::getLoai() const {
    return loai;
}

void ThuNhap::setLoai(const QString &loai) {
    this->loai = loai;
}

double ThuNhap::getSoTien() const {
    return soTien;
}

void ThuNhap::setSoTien(double soTien) {
    this->soTien = soTien;
}

QDate ThuNhap::getNgay() const {
    return ngay;
}

void ThuNhap::setNgay(const QDate &ngay) {
    this->ngay = ngay;
}