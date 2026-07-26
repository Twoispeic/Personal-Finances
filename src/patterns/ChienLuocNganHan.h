#ifndef CHIENLUOCNGANHAN_H
#define CHIENLUOCNGANHAN_H

#include "ChienLuocTietKiem.h"

class ChienLuocNganHan : public ChienLuocTietKiem
{
public:
    double phanBoTien(double soTienDu,double soTienConThieu) override ;
};

#endif // CHIENLUOCNGANHAN_H
