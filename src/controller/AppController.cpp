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

    connect(m_mucTieu, &MucTieuController::hoanTienVeHu, this, [this](double soTien) {
        QSettings settings("MyApp", "TaiChinh");
        double luyKe = settings.value(khoaSoDuLuyKe(), 0.0).toDouble();
        settings.setValue(khoaSoDuLuyKe(), luyKe + soTien);
        emit huTietKiemChanged();
    });
}

double AppController::tongThuNhap() const { return nguoiDungHienTai.tinhTongThuNhap(); }
double AppController::tongChiTieu() const { return nguoiDungHienTai.tinhTongChiTieu(); }
double AppController::soDuThang() const { return nguoiDungHienTai.tinhSoDuThang(); }


void AppController::napNguoiDung(int id) {
    datNguoiDungHienTai(id);
}

double AppController::ketThucThang() {
    traGopMucTieuDaiHanThangNay();

    // QUAN TRỌNG: phải làm mới cache của m_mucTieu NGAY sau khi trả góp, để huTietKiem() bên dưới
    // tính đúng phần tiền vừa bị trừ đi cho mục tiêu dài hạn (tránh lưu dư số dư luỹ kế).
    m_mucTieu->taiLai();

    // Chốt số dư luỹ kế của tháng đang đóng lại, làm gốc cho tháng sau.
    QSettings settings("MyApp", "TaiChinh");
    settings.setValue(khoaSoDuLuyKe(), huTietKiem());

    // KHÔNG đụng vào MucTieu: giữ nguyên toàn bộ mục tiêu ngắn/dài hạn.
    ChiTieuRepository().xoaTatCa();

    NgayMoPhong::getInstance().quaThangMoi();
    refreshDuLieu();   // dongBoNguoiDungTuDatabase() + taiLai() cho cả 3 controller + emit đủ tín hiệu

    return huTietKiem();
}



void AppController::dongBoNguoiDungTuDatabase() {
    nguoiDungHienTai.xoaDanhSachThuNhap();
    nguoiDungHienTai.xoaDanhSachChiTieu();
    nguoiDungHienTai.xoaDanhSachMucTieu();

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
    QString thangNamHienTai = NgayMoPhong::getInstance().layNgayHienTai().toString("yyyy-MM");

    QList<MucTieu*> danhSachTuDB = repo.layTatCa();

    // BƯỚC 1: FAIL-SAFE — dọn các mục tiêu bị hụt hũ bất thường trước khi tính toán tiếp
    QList<MucTieu*> conLai;
    for (MucTieu* baseMt : danhSachTuDB) {
        MucTieuDaiHan* mt = dynamic_cast<MucTieuDaiHan*>(baseMt);
        if (mt) {
            double moc = mt->getSoTienMocAnToan();
            // Chỉ áp dụng cho mục tiêu ĐÃ TỪNG có tiến độ hợp lệ (moc > 0).
            // Mục tiêu vừa tạo (moc == -1, chưa trả lần nào) không bị ảnh hưởng.
            if (moc > 0 && mt->getSoTienDaTietKiem() < moc) {
                repo.xoa(mt->getId());
                delete baseMt;
                continue;
            }
        }
        conLai.append(baseMt);
    }

    // BƯỚC 2: TRẢ GÓP — dùng 1 "hũ khả dụng" cục bộ, trừ dần cho từng mục tiêu dài hạn
    // chưa được trả trong tháng này (đảm bảo không chia vượt quá số tiền thực sự có).
    double khaDung = huTietKiem();
    double tongDaTraKyNay = 0.0;   // cộng dồn để trừ ngược lại SoDuLuyKe sau vòng lặp
    for (MucTieu* baseMt : conLai) {
        MucTieuDaiHan* mt = dynamic_cast<MucTieuDaiHan*>(baseMt);
        if (!mt) continue;

        // Đã trả trong tháng này rồi -> bỏ qua, dù bấm lại bao nhiêu lần cũng không sao
        if (mt->getThangNamDaTra() == thangNamHienTai) continue;
        if (mt->getSoTienDaTietKiem() >= mt->getSoTienMucTieu()) continue;

        // Số tiền cần trả kỳ này: không vượt quá phần còn thiếu để đạt 100%
        // (tránh trả dư ở kỳ cuối cùng nếu soTienMoiKy làm tổng vượt soTienMucTieu).
        double tienConThieu = mt->getSoTienMucTieu() - mt->getSoTienDaTietKiem();
        double tienCanTra = qMin(mt->getSoTienMoiKy(), tienConThieu);
        if (khaDung >= tienCanTra) {
            double tienMoi = mt->getSoTienDaTietKiem() + tienCanTra;
            int kyMoi = mt->getSoKyDaTra() + 1;

            repo.capNhatTrangThaiThang(mt->getId(), tienMoi, kyMoi, thangNamHienTai, tienMoi);
            khaDung -= tienCanTra;
            tongDaTraKyNay += tienCanTra;
        }
        // Nếu chưa đủ tiền: không làm gì cả — người dùng có thể thêm thu nhập / giảm chi tiêu
        // rồi bấm refresh lại sau, vẫn trong tháng này thì vẫn hợp lệ để trả.
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

    NgayMoPhong::getInstance().datTaiKhoanHienTai(id);

    refreshDuLieu();
}

void AppController::quaThangMoi() {
    NgayMoPhong::getInstance().quaThangMoi();
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