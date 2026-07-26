#include "MucTieuDaiHan.h"

MucTieuDaiHan::MucTieuDaiHan() {
    this->soKyTraGop = 0;
    this->soTienMoiKy = 0.0;
}

MucTieuDaiHan::MucTieuDaiHan(const QString& ten, double soTienMucTieu, int soKyTraGop, double soTienMoiKy)
    : MucTieu(ten, soTienMucTieu), soKyTraGop(soKyTraGop), soTienMoiKy(soTienMoiKy) {};

bool MucTieuDaiHan::kiemTraHoanThanh() {
    return (soTienDaTietKiem >= soTienMucTieu);
} 