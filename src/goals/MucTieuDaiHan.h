#ifndef MUCTIEUDAIHAN_H
#define MUCTIEUDAIHAN_H

#include "MucTieu.h"

class MucTieuDaiHan : public MucTieu {
private:
    int soKyTraGop;       // Thuộc tính riêng theo đúng UML
    double soTienMoiKy;   // Thuộc tính riêng theo đúng UML

public:
    MucTieuDaiHan();
    MucTieuDaiHan(double soTien, int kyTraGop, double tienMoiKy);

    // Override lại hàm thuần túy từ lớp cha
    bool kiemTraHoanThanh() override;
};

#endif // MUCTIEUDAIHAN_H