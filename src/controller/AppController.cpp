#include "AppController.h"
#include "database/NguoiDungRepository.h"
#include "database/ThuNhapRepository.h"
#include "database/ChiTieuRepository.h"
#include "database/MucTieuRepository.h"
#include "goals/MucTieuDaiHan.h"
#include "goals/MucTieuNganHan.h"

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
    // 1. Tính tổng tiền dư
    double conDu = tongThuNhap() - tongChiTieu();
    if (conDu <= 0) return 0.0; // Nếu không dư đồng nào thì kết thúc luôn

    MucTieuRepository repo;
    QList<MucTieu*> ds = repo.layTatCa();

    // 2. Chạy vòng lặp ưu tiên đắp tiền cho các Mục Tiêu Dài Hạn
    for (MucTieu* mt : ds) {
        // Kiểm tra ép kiểu xem đây có phải mục tiêu dài hạn không
        MucTieuDaiHan* daiHan = dynamic_cast<MucTieuDaiHan*>(mt);

        // Nếu là dài hạn, mục tiêu chưa đạt 100%, và trong túi vẫn còn dư tiền
        if (daiHan != nullptr && conDu > 0 && !daiHan->kiemTraHoanThanh()) {
            double tienCanMoiKy = daiHan->getSoTienMoiKy();

            if (tienCanMoiKy > 0) {
                // Tính số tiền rót vào: Ưu tiên rót đủ mức cần của 1 kỳ.
                // Nếu tiền dư trong túi ít hơn mức cần, thì vét sạch túi rót hết vào.
                double tienRotVao = qMin(conDu, tienCanMoiKy);

                // Cập nhật số tiền đã tích lũy vào Database
                double tienDaCo = daiHan->getSoTienDaTietKiem();
                repo.capNhatTienDaTietKiem(daiHan->getId(), tienDaCo + tienRotVao);

                // Trừ đi số tiền dư sau khi rót
                conDu -= tienRotVao;
            }
        }
    }
    qDeleteAll(ds);

    // 3. Đồng bộ lại dữ liệu để UI tự động vẽ lại thanh tiến độ
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