#include "ChienLuocDaiHan.h"
#include <algorithm>
ChienLuocDaiHan::ChienLuocDaiHan(double soTienMoiThang):soTienTraGopMoiThang( soTienMoiThang){};
double ChienLuocDaiHan::phanBoTien(double soTienDu){
    // Khi ko du tien ung thi se tra het so tien ung, ko can tra default cai ma minh da dat
    return std::min(soTienDu,soTienTraGopMoiThang);
}