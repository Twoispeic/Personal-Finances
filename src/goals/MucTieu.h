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
    int id = -1;
    bool daGopThangNay = false;
public:
    MucTieu(const QString& ten, double soTienMucTieu);
    virtual ~MucTieu();

    // Gộp từ MucTieuFactory — static factory method ngay trên chính class được tạo ra
    // (Static Factory Method, biến thể của Factory pattern không cần tách class riêng).
    // Tạo MucTieu đúng loại + tự gắn sẵn Strategy/State tương ứng.
    static MucTieu* taoMucTieuNganHan(const QString& ten, double soTienMucTieu, int thoiHanThang);
    static MucTieu* taoMucTieuDaiHan(const QString& ten, double soTienMucTieu, int soKyTraGop);

    //Từ factory mà ra
    void datChienLuoc(ChienLuocTietKiem* cl);
    void datTrangThai(TrangThaiMucTieu* tt);

    virtual double capNhatTietKiem(double soTienDu);
    virtual double tinhTienDoPhanTram();

    // Hàm thuần túy bắt buộc lớp con phải định nghĩa
    virtual bool kiemTraHoanThanh() = 0;
    //Hàm color
    QString layMauSacHienTai() const;

    QString getTenMucTieu() const;
    double getSoTienMucTieu() const;
    double getSoTienDaTietKiem() const;
    void datSoTienDaTietKiem(double soTien);

    int getId() const;
    void datId(int idMoi);

};

#endif // MUCTIEU_H