#include "MucTieuDaiHan.h"

// Constructor nhận vào số tiền mục tiêu dài hạn khớp với file .h
MucTieuDaiHan::MucTieuDaiHan(double mucTieu) {
    this->soTienMucTieu = mucTieu;
    this->soTienDaTietKiem = 0.0;
    this->soKyTraGop = 0;
    this->soTienMoiKy = 0.0;
}

bool MucTieuDaiHan::kiemTraHoanThanh() {
    return (soTienDaTietKiem >= soTienMucTieu);
}