#include "ChienLuocDaiHan.h"
#include <algorithm>

ChienLuocDaiHan::ChienLuocDaiHan(double soTienMoiThang) : soTienTraGopMoiThang(soTienMoiThang) {}

double ChienLuocDaiHan::phanBoTien(double soTienDu, double soTienConThieu) {
    double muonLay = std::min(soTienTraGopMoiThang, soTienConThieu);
    double conLaiSauKhiTra = soTienDu - muonLay;
    if (conLaiSauKhiTra < muonLay * 0.1) return 0.0;

    return std::min(soTienDu, muonLay);
}