#include "MucTieuNganHan.h"
#include <iostream>

// Constructor thiết lập số tiền ban đầu
MucTieuNganHan::MucTieuNganHan(double mucTieu) {
    this->soTienMucTieu = mucTieu;
    this->soTienDaTietKiem = 0.0;
}

// Logic đắp tiền vào mục tiêu
void MucTieuNganHan::themTienTietKiem(double tienThem) {
    if (tienThem > 0) {
        soTienDaTietKiem += tienThem;
    }

    // Sau khi thêm tiền thì tự động kiểm tra xem đã đạt mục tiêu chưa
    kiemTraHoanThanh();
}

// Logic kiểm tra trạng thái hoàn thành (Khớp kiểu bool với class cha)
bool MucTieuNganHan::kiemTraHoanThanh() {
    if (soTienDaTietKiem >= soTienMucTieu) {
        std::cout << "Chuc mung! Ban da hoan thanh muc tieu ngan han.\n";
        return true;
    } else {
        std::cout << "Tien do: " << soTienDaTietKiem << " / " << soTienMucTieu << "\n";
        return false;
    }
}