#include "MucTieuNganHan.h"

MucTieuNganHan::MucTieuNganHan() {
    this->thoiHanThang = 0;
}

MucTieuNganHan::MucTieuNganHan(const QString& ten, double soTienMucTieu, int thoiHanThang)
    : MucTieu(ten, soTienMucTieu), thoiHanThang(thoiHanThang) {}

bool MucTieuNganHan::kiemTraHoanThanh() {
    return (soTienDaTietKiem >= soTienMucTieu);
}