#include "MucTieuDaiHan.h"

MucTieuDaiHan::MucTieuDaiHan() {
    soKyTraGop = 0;
    soTienMoiKy = 0.0;
}

bool MucTieuDaiHan::kiemTraHoanThanh() {
    // Logic: Hoàn thành nếu số tiền đã tiết kiệm >= số tiền mục tiêu
    return (soTienDaTietKiem >= soTienMucTieu);
}