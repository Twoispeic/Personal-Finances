#ifndef MUCTIEUNGANHAN_H
#define MUCTIEUNGANHAN_H

#include "MucTieu.h"

class MucTieuNganHan : public MucTieu {
private:
    int thoiHanThang; // Thuộc tính riêng theo đúng UML

public:
    MucTieuNganHan();
    MucTieuNganHan(double soTien, int thoiHan);

    // Override lại hàm thuần túy từ lớp cha
    bool kiemTraHoanThanh() override;
};

#endif // MUCTIEUNGANHAN_H