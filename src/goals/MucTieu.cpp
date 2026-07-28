#include "MucTieu.h"
#include "src/patterns/ChienLuocTietKiem.h"
#include "src/patterns/TrangThaiMucTieu.h"

MucTieu::MucTieu(const QString& ten, double soTienMucTieu)
    : tenMucTieu(ten), soTienMucTieu(soTienMucTieu), soTienDaTietKiem(0.0),
    trangThai(nullptr), chienLuoc(nullptr) {}
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

