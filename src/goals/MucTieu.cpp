#include "MucTieu.h"
#include "src/patterns/ChienLuocTietKiem.h"
#include "src/patterns/TrangThaiMucTieu.h"

MucTieu::MucTieu(const QString& ten, double soTienMucTieu)
    : tenMucTieu(ten), soTienMucTieu(soTienMucTieu), soTienDaTietKiem(0.0),
    trangThai(nullptr), chienLuoc(nullptr) {}

MucTieu::~MucTieu() {
    delete chienLuoc;
    delete trangThai;
}

void MucTieu::capNhatTietKiem(double soTien) {
    if (chienLuoc != nullptr) {
        double soTienDuocPhanBo = chienLuoc->phanBoTien(soTien);
        soTienDaTietKiem += soTienDuocPhanBo;
    }
    if (trangThai != nullptr) {
        trangThai->kiemTraChuyen(this);
    }
}

double MucTieu::tinhTienDoPhanTram() {
    if (soTienMucTieu <= 0) return 0.0;
    return (soTienDaTietKiem / soTienMucTieu) * 100.0;
}


