#include "MucTieuDaiHan.h"

MucTieuDaiHan::MucTieuDaiHan(const QString& ten, double soTienMucTieu, int soKyTraGop)
    : MucTieu(ten, soTienMucTieu), soKyTraGop(soKyTraGop),
    soTienMoiKy(soKyTraGop > 0 ? soTienMucTieu / soKyTraGop : 0.0) {}
bool MucTieuDaiHan::kiemTraHoanThanh() {
    return (soTienDaTietKiem >= soTienMucTieu);
}
int MucTieuDaiHan::getSoKyTraGop() const { return soKyTraGop; }
double MucTieuDaiHan::getSoTienMoiKy() const { return soTienMoiKy; }
