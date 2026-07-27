#include "NguoiDung.h"

NguoiDung::NguoiDung() : ten(""), congViec("") {}

NguoiDung::NguoiDung(QString ten, QString congViec)
    : ten(ten), congViec(congViec) {}

QString NguoiDung::getTen() const { return ten; }
void NguoiDung::setTen(const QString &ten) { this->ten = ten; }

QString NguoiDung::getCongViec() const { return congViec; }
void NguoiDung::setCongViec(const QString &congViec) { this->congViec = congViec; }

void NguoiDung::themThuNhap(const ThuNhap &thuNhap) {
    danhSachThuNhap.append(thuNhap);
}

void NguoiDung::themChiTieu(const ChiTieu &chiTieu) {
    danhSachChiTieu.append(chiTieu);
}

MucTieu* NguoiDung::taoMucTieu(LoaiMucTieu loai) {
    return nullptr;
}

double NguoiDung::tinhTongThuNhap() const {
    double tong = 0;
    for (const auto &tn : danhSachThuNhap) {
        tong += tn.getSoTien();
    }
    return tong;
}

double NguoiDung::tinhTongChiTieu() const {
    double tong = 0;
    for (const auto &ct : danhSachChiTieu) {
        tong += ct.getSoTien();
    }
    return tong;
}

double NguoiDung::tinhSoDuThang() const {
    return tinhTongThuNhap() - tinhTongChiTieu();
}