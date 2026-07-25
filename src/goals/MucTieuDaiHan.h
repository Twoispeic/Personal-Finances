#ifndef MUCTIEUDAIHAN_H
#define MUCTIEUDAIHAN_H

#include "MucTieu.h"
#include "../patterns/TrangThaiMucTieu.h"

class MucTieuDaiHan : public MucTieu {
private:
    int soKyTraGop;
    double soTienMoiKy;

public:
    MucTieuDaiHan();
    bool kiemTraHoanThanh() override;
};

#endif // MUCTIEUDAIHAN_H