#include "MucTieuController.h"
#include "database/MucTieuRepository.h"
#include "goals/MucTieuNganHan.h"
#include "goals/MucTieuDaiHan.h"
#include "goals/MucTieu.h"

MucTieuController::MucTieuController(NguoiDung* nd, QObject* parent)
    : QObject(parent), nguoiDung(nd)
{
    MucTieuRepository().taoBang();
    taiLai();
}

QVariantList MucTieuController::danhSach() const { return m_danhSach; }
QVariantList MucTieuController::danhSachNganHan() const { return m_danhSachNganHan; }
QVariantList MucTieuController::danhSachDaiHan() const { return m_danhSachDaiHan; }
int MucTieuController::soLuongHoanThanh() const { return m_soLuongHoanThanh; }

void MucTieuController::taiLai() {
    m_danhSach.clear();
    m_danhSachNganHan.clear();
    m_danhSachDaiHan.clear();
    m_soLuongHoanThanh = 0;

    MucTieuRepository repo;
    const QList<MucTieu*> ds = repo.layTatCa();
    for (MucTieu* mt : ds) {
        QVariantMap m;
        m["id"] = mt->getId();
        m["ten"] = mt->getTenMucTieu();
        m["soTienMucTieu"] = mt->getSoTienMucTieu();
        m["soTienDaTietKiem"] = mt->getSoTienDaTietKiem();
        m["tienDo"] = mt->tinhTienDoPhanTram();
        m["mauSac"] = mt->layMauSacHienTai();

        bool laNganHan = (dynamic_cast<MucTieuNganHan*>(mt) != nullptr);
        m["laNganHan"] = laNganHan;

        // ĐƯA LÊN TRƯỚC — gán đủ dữ liệu vào "m" trước khi append
        MucTieuNganHan* ngan = dynamic_cast<MucTieuNganHan*>(mt);
        MucTieuDaiHan* dai = dynamic_cast<MucTieuDaiHan*>(mt);
        if (ngan) {
            m["thoiHanThang"] = ngan->getThoiHanThang();
        } else if (dai) {
            m["soKyTraGop"] = dai->getSoKyTraGop();
            m["soTienMoiKy"] = dai->getSoTienMoiKy();
            int soKyDaTra = dai->getSoTienMoiKy() > 0
                                ? (int)(dai->getSoTienDaTietKiem() / dai->getSoTienMoiKy()) : 0;
            m["soKyDaTra"] = soKyDaTra;
        }

        if (mt->kiemTraHoanThanh()) {
            m_soLuongHoanThanh++;
        }

        m_danhSach.append(m);
        if (laNganHan) {
            m_danhSachNganHan.append(m);
        } else {
            m_danhSachDaiHan.append(m);
        }
    }
    qDeleteAll(ds);
    emit duLieuThayDoi();
}

void MucTieuController::themNganHan(const QString& ten, double soTien, int thoiHan) {
    MucTieu* mt = MucTieu::taoMucTieuNganHan(ten, soTien, thoiHan);
    MucTieuRepository().them(mt);
    delete mt;
    taiLai();
}

void MucTieuController::themDaiHan(const QString& ten, double soTien, int soKy) {
    MucTieu* mt = MucTieu::taoMucTieuDaiHan(ten, soTien, soKy);
    MucTieuRepository().them(mt);
    delete mt;
    taiLai();
}

void MucTieuController::gop(int mucTieuId, double soTien) {
    MucTieuRepository repo;
    QList<MucTieu*> ds = repo.layTatCa();
    for (MucTieu* mt : ds) {
        if (mt->getId() == mucTieuId) {
            double daDung = nguoiDung->gopTietKiemNganHan(mt, soTien);
            repo.capNhatTienDaTietKiem(mt->getId(), mt->getSoTienDaTietKiem());
            if (daDung > 0) emit daGopTuHuTietKiem(daDung);
            break;
        }
    }
    qDeleteAll(ds);
    taiLai();
}

double MucTieuController::tongDaTietKiem() const {
    double tong = 0;
    for (const QVariant& v : m_danhSach) {
        tong += v.toMap()["soTienDaTietKiem"].toDouble();
    }
    return tong;
}

double MucTieuController::tongMucTieu() const {
    double tong = 0;
    for (const QVariant& v : m_danhSach) {
        tong += v.toMap()["soTienMucTieu"].toDouble();
    }
    return tong;
}

void MucTieuController::xoa(int id) {
    MucTieuRepository repo;
    QList<MucTieu*> ds = repo.layTatCa();
    double soTienHoanLai = 0.0;
    for (MucTieu* mt : ds) {
        if (mt->getId() == id) {
            soTienHoanLai = mt->getSoTienDaTietKiem();
            break;
        }
    }
    qDeleteAll(ds);

    repo.xoa(id);
    if (soTienHoanLai > 0) emit hoanTienVeHu(soTienHoanLai);
    taiLai();
}