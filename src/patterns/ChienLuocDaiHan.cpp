#include "ChienLuocDaiHan.h"
#include <algorithm>

ChienLuocDaiHan::ChienLuocDaiHan(double soTienMoiThang) : soTienTraGopMoiThang(soTienMoiThang) {}

double ChienLuocDaiHan::phanBoTien(double soTienDu, double soTienConThieu) {
    double muonLay = std::min(soTienTraGopMoiThang, soTienConThieu);   // không lấy dư quá phần còn thiếu
    return std::min(soTienDu, muonLay);
}