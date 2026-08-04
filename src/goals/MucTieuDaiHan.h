#ifndef MUCTIEUDAIHAN_H
#define MUCTIEUDAIHAN_H

#include "MucTieu.h"

class MucTieuDaiHan : public MucTieu {
private:
    int soKyTraGop;     // Thuộc tính riêng theo đúng UML
    double soTienMoiKy; // Thuộc tính riêng theo đúng UML
    int soKyDaTra = 0;

public:
    MucTieuDaiHan(const QString& ten, double soTienMucTieu, int soKyTraGop);

    // Override lại hàm thuần túy từ lớp cha
    bool kiemTraHoanThanh() override;
    //getter
    int getSoKyTraGop() const;
    double getSoTienMoiKy() const;

    int getSoKyDaTra() const;
    void setSoKyDaTra(int soKy);
};

#endif // MUCTIEUDAIHAN_H 