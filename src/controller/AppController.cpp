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
#include "database/NgayMoPhong.h"
#include <QSettings>
#include <QDate>
#include <QVariant>
#include <QtGlobal>

AppController::AppController(QObject* parent)
    : QObject(parent), nguoiDungHienTai("", "")
{
    NguoiDungRepository ndRepo;
    ndRepo.taoBang();
    // Tên/công việc thật được nạp SAU khi đăng nhập qua napNguoiDung(id) — xem LoginController.

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

    connect(m_mucTieu, &MucTieuController::daGopTuHuTietKiem, this, [this](double soTien) {
        QSettings settings("MyApp", "TaiChinh");
        double luyKe = settings.value(khoaSoDuLuyKe(), 0.0).toDouble();
        settings.setValue(khoaSoDuLuyKe(), luyKe - soTien);
        emit huTietKiemChanged();
    });

    // FIX: khi XÓA (huỷ) mục tiêu dang dở, hoàn lại đúng số tiền đã góp về hũ tiết kiệm —
    // ngược chiều với connect ở trên (cộng thay vì trừ).
    connect(m_mucTieu, &MucTieuController::hoanTienVeHu, this, [this](double soTien) {
        QSettings settings("MyApp", "TaiChinh");
        double luyKe = settings.value(khoaSoDuLuyKe(), 0.0).toDouble();
        settings.setValue(khoaSoDuLuyKe(), luyKe + soTien);
        emit huTietKiemChanged();
    });
}

double AppController::tongThuNhap() const { return nguoiDungHienTai.tinhTongThuNhap(); }
//Dead code
void AppController::napNguoiDung(int id) {
    NguoiDungRepository ndRepo;
    NguoiDung daLuu = ndRepo.layThongTinTheoId(id);
    nguoiDungHienTai.setTen(daLuu.getTen());
    nguoiDungHienTai.setCongViec(daLuu.getCongViec());
    emit duLieuThayDoi();
}
//end
double AppController::tongChiTieu() const { return nguoiDungHienTai.tinhTongChiTieu(); }
double AppController::soDuThang() const { return nguoiDungHienTai.tinhSoDuThang(); }

double AppController::ketThucThang() {
    traGopMucTieuDaiHanThangNay();

    m_mucTieu->taiLai();

    QSettings settings("MyApp", "TaiChinh");
    settings.setValue(khoaSoDuLuyKe(), huTietKiem());

    ChiTieuRepository().xoaTatCa();

    NgayMoPhong::quaThangMoi();
    refreshDuLieu();   // dongBoNguoiDungTuDatabase() + taiLai() cho cả 3 controller + emit đủ tín hiệu

    return huTietKiem();
}



void AppController::dongBoNguoiDungTuDatabase() {
    nguoiDungHienTai.xoaDanhSachThuNhap();
    nguoiDungHienTai.xoaDanhSachChiTieu();
    nguoiDungHienTai.xoaDanhSachMucTieu();

    // CHỈ nạp thu nhập của THÁNG HIỆN TẠI để tính thu/chi/số dư — không dùng layTatCa() nữa
    // vì từ giờ bảng ThuNhap được giữ lại (không xoá mỗi lần chốt sổ) để nuôi biểu đồ 12 tháng.
    for (const ThuNhap& tn : ThuNhapRepository().layThangHienTai())
        nguoiDungHienTai.themThuNhap(tn);

    for (const ChiTieu& ct : ChiTieuRepository().layTatCa())
        nguoiDungHienTai.themChiTieu(ct);

    for (MucTieu* mt : MucTieuRepository().layTatCa())
        nguoiDungHienTai.themMucTieuVaoDanhSach(mt);   // chuyển quyền sở hữu cho NguoiDung, KHÔNG delete ở đây
}

double AppController::huTietKiem() const {
    QSettings settings("MyApp", "TaiChinh");
    double luyKe = settings.value(khoaSoDuLuyKe(), 0.0).toDouble();
    double con = luyKe + soDuThang();
    return con > 0 ? con : 0;
}


void AppController::hoanThanhMucTieu(int id) {
    MucTieuRepository repo;
    repo.xoa(id);

    dongBoNguoiDungTuDatabase();
    m_mucTieu->taiLai();
    emit duLieuThayDoi();
}

void AppController::lamMoiMucTieu() {
    traGopMucTieuDaiHanThangNay();

    m_mucTieu->taiLai();
    emit huTietKiemChanged();
    emit duLieuThayDoi();
}

void AppController::traGopMucTieuDaiHanThangNay() {
    MucTieuRepository repo;
    QString thangNamHienTai = NgayMoPhong::layNgayHienTai().toString("yyyy-MM");

    QList<MucTieu*> danhSachTuDB = repo.layTatCa();

    QList<MucTieu*> conLai;
    for (MucTieu* baseMt : danhSachTuDB) {
        MucTieuDaiHan* mt = dynamic_cast<MucTieuDaiHan*>(baseMt);
        if (mt) {
            double moc = mt->getSoTienMocAnToan();
            if (moc > 0 && mt->getSoTienDaTietKiem() < moc) {
                repo.xoa(mt->getId());
                delete baseMt;
                continue;
            }
        }
        conLai.append(baseMt);
    }

    double khaDung = huTietKiem();
    double tongDaTraKyNay = 0.0;   // cộng dồn để trừ ngược lại SoDuLuyKe sau vòng lặp
    for (MucTieu* baseMt : conLai) {
        MucTieuDaiHan* mt = dynamic_cast<MucTieuDaiHan*>(baseMt);
        if (!mt) continue;

        if (mt->getThangNamDaTra() == thangNamHienTai) continue;

        if (mt->getSoTienDaTietKiem() >= mt->getSoTienMucTieu()) continue;

        double tienConThieu = mt->getSoTienMucTieu() - mt->getSoTienDaTietKiem();
        double tienCanTra = qMin(mt->getSoTienMoiKy(), tienConThieu);
        if (khaDung >= tienCanTra) {
            double tienThucTra = mt->capNhatTietKiem(khaDung);
                double tienMoi = mt->getSoTienDaTietKiem();   // Strategy đã cộng dồn sẵn bên trong
                int kyMoi = mt->getSoKyDaTra() + 1;

                repo.capNhatTrangThaiThang(mt->getId(), tienMoi, kyMoi, thangNamHienTai, tienMoi);
                khaDung -= tienThucTra;
                tongDaTraKyNay += tienThucTra;
        }
    }


    if (tongDaTraKyNay > 0) {
        QSettings settings("MyApp", "TaiChinh");
        double luyKe = settings.value(khoaSoDuLuyKe(), 0.0).toDouble();
        settings.setValue(khoaSoDuLuyKe(), luyKe - tongDaTraKyNay);
    }

    qDeleteAll(conLai);
    dongBoNguoiDungTuDatabase();
}
void AppController::datNguoiDungHienTai(int id) {
    ChiTieuRepository().taoBang();
    ThuNhapRepository().taoBang();
    MucTieuRepository().taoBang();

    // Nạp tên hiển thị / công việc theo tài khoản vừa đăng nhập.
    NguoiDungRepository ndRepo;
    NguoiDung nd = ndRepo.layThongTinTheoId(id);
    nguoiDungHienTai.setTen(nd.getTen());
    nguoiDungHienTai.setCongViec(nd.getCongViec());
    m_nguoiDungId = id;
    NgayMoPhong::datTaiKhoanHienTai(id);

    refreshDuLieu();
}

void AppController::quaThangMoi() {
    NgayMoPhong::quaThangMoi();
    // Sau khi chuyển tháng, cần refresh toàn bộ
    refreshDuLieu();
}

void AppController::refreshDuLieu() {
    dongBoNguoiDungTuDatabase();   // private, nhưng gọi trong class
    m_thuNhap->taiLai();
    m_chiTieu->taiLai();
    m_mucTieu->taiLai();
    emit duLieuThayDoi();
    emit huTietKiemChanged();      // nếu signal này tồn tại
}

void AppController::resetThangVaHuTietKiem() {
    QSettings settings("MyApp", "TaiChinh");
    settings.remove(khoaSoDuLuyKe());
    settings.remove(QString("ThangMoPhongHienTai_%1").arg(m_nguoiDungId));

    refreshDuLieu();
}