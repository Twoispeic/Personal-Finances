#include "MucTieu.h"

MucTieu::MucTieu() {
    this->tenMucTieu = "";
    this->soTienMucTieu = 0.0;
    this->soTienDaTietKiem = 0.0;
    this->trangThai = nullptr;
    this->chienLuoc = nullptr;
}

MucTieu::~MucTieu() {}

void MucTieu::capNhatTietKiem(double soTien) {
    if (soTien > 0) {
        this->soTienDaTietKiem += soTien;
    }
}

double MucTieu::tinhTienDoPhanTram() {
    if (soTienMucTieu <= 0) return 0.0;
    return (soTienDaTietKiem / soTienMucTieu) * 100.0;
}