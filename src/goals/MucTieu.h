#ifndef MUCTIEU_H
#define MUCTIEU_H

#include <QString>

// Khai báo trước cho các class Design Pattern
class TrangThaiMucTieu;
class ChienLuocTietKiem;

class MucTieu {
protected:
    QString tenMucTieu;
    double soTienMucTieu;
    double soTienDaTietKiem;
    TrangThaiMucTieu* trangThai;
    ChienLuocTietKiem* chienLuoc;

public:
    MucTieu();
    virtual ~MucTieu();

    virtual void capNhatTietKiem(double soTien);
    virtual double tinhTienDoPhanTram();

    // Hàm ảo thuần túy biến class này thành abstract
    virtual bool kiemTraHoanThanh() = 0;
};

#endif // MUCTIEU_H