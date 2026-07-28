#include "ChiTieu.h"

ChiTieu::ChiTieu() : loai(KHAC), soTien(0.0), ngay(QDate::currentDate()) {}

ChiTieu::ChiTieu(LoaiChiTieu loai, double soTien, QDate ngay)
    : loai(loai), soTien(soTien), ngay(ngay) {}

double ChiTieu::getSoTien() const { return soTien; }
LoaiChiTieu ChiTieu::getLoai() const { return loai; }
QDate ChiTieu::getNgay() const { return ngay; }

void ChiTieu::setSoTien(double soTien) { this->soTien = soTien; }
void ChiTieu::setLoai(LoaiChiTieu loai) { this->loai = loai; }
void ChiTieu::setNgay(const QDate& ngay) { this->ngay = ngay; }