#ifndef MUCTIEUDAIHAN_H
#define MUCTIEUDAIHAN_H

#include "MucTieu.h"

class MucTieuDaiHan : public MucTieu {
private:
    bool m_daGopThangNay = false;
    int soKyTraGop;     // Thuộc tính riêng theo đúng UML
    double soTienMoiKy; // Thuộc tính riêng theo đúng UML
    int soKyDaTra = 0;

public:
    MucTieuDaiHan(const QString& ten, double soTienMucTieu, int soKyTraGop);
    bool getDaGopThangNay() const { return m_daGopThangNay; }
    void setDaGopThangNay(bool status) { m_daGopThangNay = status; };

    // Override lại hàm thuần túy từ lớp cha
    bool kiemTraHoanThanh() override;
    //getter
    int getSoKyTraGop() const;
    double getSoTienMoiKy() const;

    //getter & setter cho soKyDaTra
    int getSoKyDaTra() const { return soKyDaTra; }
    void setSoKyDaTra(int soKy) { soKyDaTra = soKy; }
};

#endif // MUCTIEUDAIHAN_H 