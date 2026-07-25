#include "MucTieuDaiHan.h"

MucTieuDaiHan::MucTieuDaiHan() {
    this->soKyTraGop = 0;
    this->soTienMoiKy = 0.0;
}

MucTieuDaiHan::MucTieuDaiHan(double soTien, int kyTraGop, double tienMoiKy) {
    this->soTienMucTieu = soTien;
    this->soKyTraGop = kyTraGop;
    this->soTienMoiKy = tienMoiKy;
    this->soTienDaTietKiem = 0.0;
}

bool MucTieuDaiHan::kiemTraHoanThanh() {
    return (soTienDaTietKiem >= soTienMucTieu);
} 