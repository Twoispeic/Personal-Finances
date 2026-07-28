#ifndef MUCTIEUNGANHAN_H
#define MUCTIEUNGANHAN_H

#include "MucTieu.h"

class MucTieuNganHan : public MucTieu {
private:
    int thoiHanThang; // Thuộc tính riêng theo đúng UML

public:
    MucTieuNganHan(const QString& ten, double soTienMucTieu, int thoiHanThang);

    // Override lại hàm thuần túy từ lớp cha
    bool kiemTraHoanThanh() override;
    //Getter
    int getThoiHanThang() const;
};

#endif // MUCTIEUNGANHAN_H