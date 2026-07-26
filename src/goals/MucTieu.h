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
    MucTieu(const QString& ten, double soTienMucTieu);

    //Từ factory mà ra
    void datChienLuoc(ChienLuocTietKiem* cl);
    void datTrangThai(TrangThaiMucTieu* tt);

    virtual void capNhatTietKiem(double soTien);
    virtual double tinhTienDoPhanTram();

    // Hàm thuần túy bắt buộc lớp con phải định nghĩa
    virtual bool kiemTraHoanThanh() = 0;
    //Hàm color
    QString layMauSacHienTai() const;
};

#endif // MUCTIEU_H 