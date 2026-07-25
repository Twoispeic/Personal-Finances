#ifndef MUCTIEU_H
#define MUCTIEU_H

#include <QString>

// Khai báo trước cho các lớp Design Pattern liên quan
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

    // Hàm thuần túy bắt buộc lớp con phải định nghĩa
    virtual bool kiemTraHoanThanh() = 0;
};

#endif // MUCTIEU_H