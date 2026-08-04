#ifndef MUCTIEUDAIHAN_H
#define MUCTIEUDAIHAN_H

#include "MucTieu.h"

class MucTieuDaiHan : public MucTieu {
private:
    bool m_daGopThangNay = false;
    int soKyTraGop;     // Thuộc tính riêng theo đúng UML
    double soTienMoiKy; // Thuộc tính riêng theo đúng UML
    int soKyDaTra = 0;
    QString thangNamDaTra = "";        // lưu "yyyy-MM" của lần trả gần nhất
    double soTienMocAnToan = -1;       // mốc an toàn để fail-safe

public:
    MucTieuDaiHan(const QString& ten, double soTienMucTieu, int soKyTraGop);
    bool getDaGopThangNay() const { return m_daGopThangNay; }
    void setDaGopThangNay(bool status) { m_daGopThangNay = status; };

    // Override lại hàm thuần túy từ lớp cha
    bool kiemTraHoanThanh() override;
    //getter
    int getSoKyTraGop() const;
    double getSoTienMoiKy() const;

    int getSoKyDaTra() const;
    void setSoKyDaTra(int ky);

    QString getThangNamDaTra() const { return thangNamDaTra; }
    void setThangNamDaTra(const QString& t) { thangNamDaTra = t; }

    double getSoTienMocAnToan() const { return soTienMocAnToan; }
    void setSoTienMocAnToan(double t) { soTienMocAnToan = t; }
};

#endif // MUCTIEUDAIHAN_H 