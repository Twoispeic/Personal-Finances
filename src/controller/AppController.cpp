#include "AppController.h"
#include "database/NguoiDungRepository.h"
#include "database/ThuNhapRepository.h"
#include "database/ChiTieuRepository.h"
#include "database/MucTieuRepository.h"
#include <QSettings>
#include <QDate>

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
    double conDu = nguoiDungHienTai.phanBoTienTietKiem();
    dongBoNguoiDungTuDatabase();

    // Cập nhật lại tiền đã tiết kiệm trong DB cho từng mục tiêu dài hạn vừa được cộng thêm
    MucTieuRepository repo;
    for (MucTieu* mt : nguoiDungHienTai.layDanhSachMucTieu()) {   // cần getter này, xem ghi chú bên dưới
        repo.capNhatTienDaTietKiem(mt->getId(), mt->getSoTienDaTietKiem());
    }

    m_mucTieu->taiLai();
    emit duLieuThayDoi();
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
    double con = soDuThang() - m_mucTieu->tongDaTietKiem();
    return con > 0 ? con : 0;
}
bool AppController::thuTrichTienTuHuVaoDaiHan() {
    QSettings settings("MyApp", "TaiChinh");
    QString thangHienTai = QDate::currentDate().toString("MM-yyyy");
    QString thangDaTrichCuoi = settings.value("ThangDaTrichDaiHan", "").toString();

    // KIỂM TRA: Nếu đã trích tiền trong tháng này rồi thì không làm gì cả
    if (thangDaTrichCuoi == thangHienTai) {
        return false; // Báo lỗi về QML
    }

    // 1. Phân bổ tiền
    nguoiDungHienTai.phanBoTienTietKiem();

    // 2. Lưu Database
    MucTieuRepository repo;
    for (MucTieu* mt : nguoiDungHienTai.layDanhSachMucTieu()) {
        repo.capNhatTienDaTietKiem(mt->getId(), mt->getSoTienDaTietKiem());
    }

    // 3. LƯU LẠI THÁNG NÀY ĐÃ TRÍCH THÀNH CÔNG
    settings.setValue("ThangDaTrichDaiHan", thangHienTai);

    // 4. Cập nhật UI
    m_mucTieu->taiLai();
    emit duLieuThayDoi();

    return true; // Thành công
}