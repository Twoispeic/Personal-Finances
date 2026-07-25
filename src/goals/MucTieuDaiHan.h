#ifndef MUC TIEU DAI HAN_H
#define MUCTIEUDAIHAN_H

#include "MucTieu.h"

class MucTieuDaiHan : public MucTieu {
private:
    int soKyTraGop;
    double soTienMoiKy;

public:
    // Khai báo constructor có nhận tham số double
    MucTieuDaiHan(double mucTieu);

    // Override hàm kiểm tra hoàn thành từ class cha
    bool kiemTraHoanThanh() override;
};

#endif