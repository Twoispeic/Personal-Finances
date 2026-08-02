#include "ChiTieuController.h"
#include "database/ChiTieuRepository.h"

ChiTieuController::ChiTieuController(NguoiDung* nd, QObject* parent)
    : QObject(parent), nguoiDung(nd)
{
    ChiTieuRepository().taoBang();
    taiLai();
}

QVariantList ChiTieuController::danhSach() const { return m_danhSach; }

void ChiTieuController::taiLai() {
    m_danhSach.clear();
    for (const ChiTieu& ct : ChiTieuRepository().layTatCa()) {
        QVariantMap m;
        m["loai"] = (int)ct.getLoai();
        m["soTien"] = ct.getSoTien();
        m["ngay"] = ct.getNgay().toString("dd/MM/yyyy");
        m_danhSach.append(m);
    }
    emit duLieuThayDoi();
}

void ChiTieuController::them(int loai, double soTien) {
    ChiTieuRepository().them(ChiTieu((LoaiChiTieu)loai, soTien, QDate::currentDate()));
    taiLai();
}

void ChiTieuController::locTheoLoai(int loai) {
    m_danhSach.clear();
    for (const ChiTieu& ct : ChiTieuRepository().locTheoLoai((LoaiChiTieu)loai)) {
        QVariantMap m;
        m["loai"] = (int)ct.getLoai();
        m["soTien"] = ct.getSoTien();
        m["ngay"] = ct.getNgay().toString("dd/MM/yyyy");
        m_danhSach.append(m);
    }
    emit duLieuThayDoi();
}

void ChiTieuController::locTatCa() {
    taiLai();
}