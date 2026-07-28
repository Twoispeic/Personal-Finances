#include "MucTieuNganHan.h"

MucTieuNganHan::MucTieuNganHan(const QString& ten, double soTienMucTieu, int thoiHanThang)
    : MucTieu(ten, soTienMucTieu), thoiHanThang(thoiHanThang) {}

bool MucTieuNganHan::kiemTraHoanThanh() {
    return (soTienDaTietKiem >= soTienMucTieu);
}

int MucTieuNganHan::getThoiHanThang() const { return thoiHanThang; }