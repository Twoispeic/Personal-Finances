#ifndef CHIENLUOCDAIHAN_H
#define CHIENLUOCDAIHAN_H

#include "ChienLuocTietKiem.h"

class ChienLuocDaiHan : public ChienLuocTietKiem
{
private:
    double soTienTraGopMoiThang;
public:
    ChienLuocDaiHan(double soTienMoiThang);
    double phanBoTien(double soTienDu, double soTienConThieu) override ;
};

#endif // CHIENLUOCDAIHAN_H
