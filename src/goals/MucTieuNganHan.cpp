#include "MucTieuNganHan.h"

MucTieuNganHan::MucTieuNganHan() {
    this->thoiHanThang = 0;
}

MucTieuNganHan::MucTieuNganHan(double soTien, int thoiHan) {
    this->soTienMucTieu = soTien;
    this->thoiHanThang = thoiHan;
    this->soTienDaTietKiem = 0.0;
}

bool MucTieuNganHan::kiemTraHoanThanh() {
    return (soTienDaTietKiem >= soTienMucTieu);
}