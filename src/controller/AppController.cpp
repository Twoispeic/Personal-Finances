#include "AppController.h"
#include "database/NguoiDungRepository.h"
#include "database/ThuNhapRepository.h"
#include "database/ChiTieuRepository.h"
#include "database/MucTieuRepository.h"
#include "goals/MucTieuDaiHan.h"
#include "AppController.h"
#include "database/NguoiDungRepository.h"
#include "database/ThuNhapRepository.h"
#include "database/ChiTieuRepository.h"
#include "database/MucTieuRepository.h"
#include "goals/MucTieuDaiHan.h"
#include <QSettings>
#include <QDate>
#include <QVariant>

AppController::AppController(QObject* parent)
    : QObject(parent), nguoiDungHienTai("", "")
{
    NguoiDungRepository ndRepo;
    ndRepo.taoBang();
    NguoiDung daLuu = ndRepo.layThongTinNguoiDung();
    nguoiDungHienTai.setTen(daLuu.getTen());
    nguoiDungHienTai.setCongViec(daLuu.getCongViec());

    m_chiTieu = new ChiTieuController(&nguoiDungHienTai, this);
    m_thuNhap = new ThuNhapController(&nguoiDungHienTai, this);
    m_mucTieu = new MucTieuController(&nguoiDungHienTai, this);

    dongBoNguoiDungTuDatabase();   // đồng bộ ngay lúc khởi động

    // Đổi 2 kết nối này — đồng bộ lại RAM mỗi khi ChiTieu/ThuNhap đổi
    connect(m_chiTieu, &ChiTieuController::duLieuThayDoi, this, [this]() {
        dongBoNguoiDungTuDatabase();
        emit duLieuThayDoi();
    });
    connect(m_thuNhap, &ThuNhapController::duLieuThayDoi, this, [this]() {
        dongBoNguoiDungTuDatabase();
        emit duLieuThayDoi();
    });
    connect(m_mucTieu, &MucTieuController::duLieuThayDoi, this, [this]() {
        dongBoNguoiDungTuDatabase();
        emit duLieuThayDoi();
    });
}

double AppController::tongThuNhap() const { return nguoiDungHienTai.tinhTongThuNhap(); }
double AppController::tongChiTieu() const { return nguoiDungHienTai.tinhTongChiTieu(); }
double AppController::soDuThang() const { return nguoiDungHienTai.tinhSoDuThang(); }

double AppController::ketThucThang() {
    // Giữ lại thuật toán chốt sổ mới của Kha (Nhánh main)
    double kha = huTietKiem();
    double conDu = nguoiDungHienTai.phanBoTienTietKiem(kha);

    MucTieuRepository repo;
    for (MucTieu* mt : nguoiDungHienTai.layDanhSachMucTieu())
        repo.capNhatTienDaTietKiem(mt->getId(), mt->getSoTienDaTietKiem());

    // Lưu phần dư còn lại làm gốc cho tháng sau, rồi xoá sạch thu/chi tháng này
    QSettings settings("MyApp", "TaiChinh");
    settings.setValue("SoDuLuyKe", huTietKiem());   // tính lại sau khi đã trừ phần vừa phân bổ dài hạn

    ThuNhapRepository().xoaTatCa();
    ChiTieuRepository().xoaTatCa();

    dongBoNguoiDungTuDatabase();
    m_mucTieu->taiLai();
    emit duLieuThayDoi();

    // Trả về phần tiền dư (nếu còn) sau khi đã rót cho dài hạn
    return conDu;
}



void AppController::dongBoNguoiDungTuDatabase() {
    nguoiDungHienTai.xoaDanhSachThuNhap();
    nguoiDungHienTai.xoaDanhSachChiTieu();
    nguoiDungHienTai.xoaDanhSachMucTieu();

    for (const ThuNhap& tn : ThuNhapRepository().layTatCa())
        nguoiDungHienTai.themThuNhap(tn);

    for (const ChiTieu& ct : ChiTieuRepository().layTatCa())
        nguoiDungHienTai.themChiTieu(ct);

    for (MucTieu* mt : MucTieuRepository().layTatCa())
        nguoiDungHienTai.themMucTieuVaoDanhSach(mt);   // chuyển quyền sở hữu cho NguoiDung, KHÔNG delete ở đây
}

double AppController::huTietKiem() const {
    QSettings settings("MyApp", "TaiChinh");
    double luyKe = settings.value("SoDuLuyKe", 0.0).toDouble();
    double con = luyKe + soDuThang() - m_mucTieu->tongDaTietKiem();
    return con > 0 ? con : 0;
}

void AppController::lamMoiMucTieu() {
    // 1. Lấy danh sách QVariant
    QVariantList danhSach = m_mucTieu->danhSachDaiHan();

    // 2. Lặp qua từng QVariant thay vì auto*
    for (const QVariant& var : danhSach) {

        // 3. Ép kiểu QVariant về lại con trỏ MucTieuDaiHan*
        MucTieuDaiHan* mt = var.value<MucTieuDaiHan*>();

        // Kiểm tra an toàn: nếu ép kiểu thất bại (null) thì bỏ qua
        if (!mt) continue;

        if (mt->getDaGopThangNay()) continue;

        double tienCanTra = mt->getSoTienMoiKy();

        if (huTietKiem() >= tienCanTra) {
            double tienDaCo = mt->getSoTienDaTietKiem();
            mt->datSoTienDaTietKiem(tienDaCo + tienCanTra);

            mt->setSoKyDaTra(mt->getSoKyDaTra() + 1);
            mt->setDaGopThangNay(true);
        }
    }

    emit huTietKiemChanged();
}