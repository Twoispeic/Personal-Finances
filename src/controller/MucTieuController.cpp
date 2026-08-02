#include "MucTieuController.h"
#include "database/MucTieuRepository.h"
#include "goals/MucTieuNganHan.h"

MucTieuController::MucTieuController(NguoiDung* nd, QObject* parent)
    : QObject(parent), nguoiDung(nd)
{
    MucTieuRepository().taoBang();
    taiLai();
}

QVariantList MucTieuController::danhSach() const { return m_danhSach; }

void MucTieuController::taiLai() {
    m_danhSach.clear();
    MucTieuRepository repo;
    QList<MucTieu*> ds = repo.layTatCa();
    for (MucTieu* mt : ds) {
        QVariantMap m;
        m["id"] = mt->getId();
        m["ten"] = mt->getTenMucTieu();
        m["soTienMucTieu"] = mt->getSoTienMucTieu();
        m["soTienDaTietKiem"] = mt->getSoTienDaTietKiem();
        m["tienDo"] = mt->tinhTienDoPhanTram();
        m["mauSac"] = mt->layMauSacHienTai();
        m["laNganHan"] = (dynamic_cast<MucTieuNganHan*>(mt) != nullptr);
        m_danhSach.append(m);
    }
    qDeleteAll(ds);
    emit duLieuThayDoi();
}

void MucTieuController::themNganHan(const QString& ten, double soTien, int thoiHan) {
    MucTieu* mt = nguoiDung->taoMucTieuNganHan(ten, soTien, thoiHan);
    MucTieuRepository().them(mt);
    delete mt;
    taiLai();
}

void MucTieuController::themDaiHan(const QString& ten, double soTien, int soKy) {
    MucTieu* mt = nguoiDung->taoMucTieuDaiHan(ten, soTien, soKy);
    MucTieuRepository().them(mt);
    delete mt;
    taiLai();
}

void MucTieuController::gop(int mucTieuId, double soTien) {
    MucTieuRepository repo;
    QList<MucTieu*> ds = repo.layTatCa();
    for (MucTieu* mt : ds) {
        if (mt->getId() == mucTieuId) {
            nguoiDung->gopTietKiemNganHan(mt, soTien);
            repo.capNhatTienDaTietKiem(mt->getId(), mt->getSoTienDaTietKiem());
            break;
        }
    }
    qDeleteAll(ds);
    taiLai();
}