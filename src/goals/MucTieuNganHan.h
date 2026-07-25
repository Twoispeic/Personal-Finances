#ifndef MUCTIEUNGANHAN_H
#define MUCTIEUNGANHAN_H

#include "MucTieu.h"

class MucTieuNganHan : public MucTieu {
private:
    int thoiHanThang; // Thuộc tính riêng theo hình 4

public:
    MucTieuNganHan();
    bool kiemTraHoanThanh() ; // Ghi đè hàm của lớp cha
};

#endif // MUCTIEUNGANHAN_H