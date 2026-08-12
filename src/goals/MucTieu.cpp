#include "MucTieu.h"
#include "MucTieuNganHan.h"
#include "MucTieuDaiHan.h"
#include "src/patterns/ChienLuocTietKiem.h"
#include "src/patterns/ChienLuocNganHan.h"
#include "src/patterns/ChienLuocDaiHan.h"
#include "src/patterns/TrangThaiMucTieu.h"
#include "src/patterns/TrangThaiChuaXong.h"

MucTieu::MucTieu(const QString& ten, double soTienMucTieu)
    : tenMucTieu(ten), soTienMucTieu(soTienMucTieu), soTienDaTietKiem(0.0),
    trangThai(nullptr), chienLuoc(nullptr) {}

// Gộp từ MucTieuFactory — tạo đúng loại MucTieu + tự gắn sẵn Strategy/State tương ứng.
MucTieu* MucTieu::taoMucTieuNganHan(const QString& ten, double soTienMucTieu, int thoiHanThang) {
    MucTieu* mt = new MucTieuNganHan(ten, soTienMucTieu, thoiHanThang);
    mt->datChienLuoc(new ChienLuocNganHan());
    mt->datTrangThai(new TrangThaiChuaXong());
    return mt;
}

MucTieu* MucTieu::taoMucTieuDaiHan(const QString& ten, double soTienMucTieu, int soKyTraGop) {
    MucTieu* mt = new MucTieuDaiHan(ten, soTienMucTieu, soKyTraGop);
    double soTienMoiKy = static_cast<MucTieuDaiHan*>(mt)->getSoTienMoiKy();
    mt->datChienLuoc(new ChienLuocDaiHan(soTienMoiKy));   // Strategy vẫn cần số tiền/kỳ, lấy từ MucTieu vừa tạo
    mt->datTrangThai(new TrangThaiChuaXong());
    return mt;
}

//Factory
void MucTieu::datChienLuoc(ChienLuocTietKiem* cl) {
    chienLuoc = cl;
}

void MucTieu::datTrangThai(TrangThaiMucTieu* tt) {
    trangThai = tt;
}

QString MucTieu::layMauSacHienTai() const {
    return trangThai != nullptr ? trangThai->layMauSac() : "gray";
}
//Deconstructor
MucTieu::~MucTieu() {
    delete chienLuoc;
    delete trangThai;
}

double MucTieu::capNhatTietKiem(double soTienDu) {
    double conThieu = soTienMucTieu - soTienDaTietKiem;
    if (conThieu <= 0) return 0.0;   // đã xong, không nhận thêm

    double daDung = 0.0;
    if (chienLuoc != nullptr) {
        daDung = chienLuoc->phanBoTien(soTienDu, conThieu);
        soTienDaTietKiem += daDung;
    }
    if (trangThai != nullptr) {
        trangThai->kiemTraChuyen(this);
    }
    return daDung;
}
double MucTieu::tinhTienDoPhanTram() {
    if (soTienMucTieu <= 0) return 0.0;
    return (soTienDaTietKiem / soTienMucTieu) * 100.0;
}

QString MucTieu::getTenMucTieu() const { return tenMucTieu; }

double MucTieu::getSoTienMucTieu() const { return soTienMucTieu; }

double MucTieu::getSoTienDaTietKiem() const { return soTienDaTietKiem; }

void MucTieu::datSoTienDaTietKiem(double soTien) { soTienDaTietKiem = soTien; }

int MucTieu::getId() const { return id; }
void MucTieu::datId(int idMoi) { id = idMoi; }