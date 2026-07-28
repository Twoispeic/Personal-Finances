#include "NguoiDung.h"
#include"src/goals/MucTieuFactory.h"
#include "goals/MucTieuNganHan.h"
#include "goals/MucTieuDaiHan.h"
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

MucTieu* NguoiDung::taoMucTieuNganHan(const QString& ten, double soTienMucTieu, int thoiHanThang) {
    MucTieu* mt = MucTieuFactory::taoMucTieuNganHan(ten, soTienMucTieu, thoiHanThang);
    danhSachMucTieu.append(mt);
    return mt;
}

MucTieu* NguoiDung::taoMucTieuDaiHan(const QString& ten, double soTienMucTieu, int soKyTraGop, double soTienMoiKy) {
    MucTieu* mt = MucTieuFactory::taoMucTieuDaiHan(ten, soTienMucTieu, soKyTraGop, soTienMoiKy);
    danhSachMucTieu.append(mt);
    return mt;
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

void NguoiDung::phanBoTienTietKiem() {
    double conLai = tinhSoDuThang();
    if (conLai <= 0) return;   // tháng này âm/hòa vốn, không có gì để tiết kiệm

    // Bước 1: ưu tiên dài hạn trước
    for (MucTieu* mt : danhSachMucTieu) {
        if (dynamic_cast<MucTieuDaiHan*>(mt) != nullptr) {
            conLai -= mt->capNhatTietKiem(conLai);
            if (conLai <= 0) break;
        }
    }

    // Bước 2: còn dư thì tally vào ngắn hạn
    for (MucTieu* mt : danhSachMucTieu) {
        if (dynamic_cast<MucTieuNganHan*>(mt) != nullptr) {
            conLai -= mt->capNhatTietKiem(conLai);
            if (conLai <= 0) break;
        }
    }
}