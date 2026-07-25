#ifndef CHIENLUOCDEUDAN_H
#define CHIENLUOCDEUDAN_H

#include "ChienLuocTietKiem.h"
#include <QDebug>

class ChienLuocDeuDan : public ChienLuocTietKiem {
public:
    void phanBoTien(double soTien) override {
        qDebug() << "Thuc hien chien luoc tiet kiem deu dan voi so tien:" << soTien;
        // Logic tính toán chia đều số tiền thực tế sẽ viết ở đây
    }
};

#endif // CHIENLUOCDEUDAN_H