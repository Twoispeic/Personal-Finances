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
    // Trả góp dài hạn tháng này nếu CHƯA được trả (vd. người dùng chưa từng bấm refresh tháng này).
    // Nếu đã trả rồi (do bấm refresh trước đó) thì hàm này sẽ tự bỏ qua — không trả trùng.
    traGopMucTieuDaiHanThangNay();

    // QUAN TRỌNG: phải làm mới cache của m_mucTieu NGAY sau khi trả góp, để huTietKiem() bên dưới
    // tính đúng phần tiền vừa bị trừ đi cho mục tiêu dài hạn (tránh lưu dư số dư luỹ kế).
    m_mucTieu->taiLai();

    // Chốt số dư luỹ kế của tháng đang đóng lại, làm gốc cho tháng sau.
    QSettings settings("MyApp", "TaiChinh");
    settings.setValue("SoDuLuyKe", huTietKiem());

    // CHỈ xoá Chi Tiêu tháng này để bắt đầu tháng mới (ChiTieu không cần giữ lịch sử).
    // KHÔNG xoá ThuNhap: mỗi tháng chỉ có đúng 1 dòng (do luuThang() upsert theo tháng),
    // xoá đi sẽ làm mất luôn dữ liệu biểu đồ 12 tháng ở trang Thu Nhập.
    // KHÔNG đụng vào MucTieu: giữ nguyên toàn bộ mục tiêu ngắn/dài hạn.
    ChiTieuRepository().xoaTatCa();

    // Gộp luôn bước sang tháng mới + refresh toàn bộ VÀO CHUNG 1 lần gọi atomic — tránh việc
    // QML phải tự gọi thêm quaThangMoi() riêng, dễ quên/lệch thứ tự gây ra bug hũ tiết kiệm
    // "reset" sai và ChiTieuController không được taiLai() nên vẫn hiện chi tiêu cũ.
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
    // Hũ tiết kiệm = phần dư luỹ kế đã chốt của các tháng trước + số dư (thu - chi) đang chạy
    // của tháng hiện tại (chưa chốt). Ngay sau khi ketThucThang() chạy xong, tháng mới chưa có
    // ThuNhap/ChiTieu nào -> soDuThang() = 0 -> huTietKiem() = đúng bằng SoDuLuyKe vừa lưu.
    QSettings settings("MyApp", "TaiChinh");
    double luyKe = settings.value("SoDuLuyKe", 0.0).toDouble();
    double con = luyKe + soDuThang();
    return con > 0 ? con : 0;
}


void AppController::hoanThanhMucTieu(int id) {
    MucTieuRepository repo;
    QList<MucTieu*> ds = repo.layTatCa();

    double soTienDaTietKiemCuaMucTieu = 0.0;
    bool timThay = false;
    for (MucTieu* mt : ds) {
        if (mt->getId() == id) {
            soTienDaTietKiemCuaMucTieu = mt->getSoTienDaTietKiem();
            timThay = true;
            break;
        }
    }
    qDeleteAll(ds);

    if (!timThay) return;

    QSettings settings("MyApp", "TaiChinh");
    double luyKe = settings.value("SoDuLuyKe", 0.0).toDouble();
    settings.setValue("SoDuLuyKe", luyKe - soTienDaTietKiemCuaMucTieu);

    repo.xoa(id);

    dongBoNguoiDungTuDatabase();
    m_mucTieu->taiLai();
    emit huTietKiemChanged();
    emit duLieuThayDoi();
}

void AppController::lamMoiMucTieu() {
    // Toàn bộ logic (khoá 1 lần/tháng + fail-safe) nằm trong hàm dùng chung này,
    // để refresh và chốt sổ không bao giờ trả trùng nhau trong cùng 1 tháng.
    traGopMucTieuDaiHanThangNay();

    m_mucTieu->taiLai();
    emit huTietKiemChanged();
    emit duLieuThayDoi();
}

void AppController::traGopMucTieuDaiHanThangNay() {
    MucTieuRepository repo;
    QString thangNamHienTai = NgayMoPhong::layNgayHienTai().toString("yyyy-MM");

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
    for (MucTieu* baseMt : conLai) {
        MucTieuDaiHan* mt = dynamic_cast<MucTieuDaiHan*>(baseMt);
        if (!mt) continue;

        // Đã trả trong tháng này rồi -> bỏ qua, dù bấm lại bao nhiêu lần cũng không sao
        if (mt->getThangNamDaTra() == thangNamHienTai) continue;

        // ĐÃ ĐẠT 100% (hoặc vượt) RỒI -> mục tiêu đã hoàn thành, KHÔNG trả góp thêm nữa,
        // dù đã sang tháng mới và thangNamDaTra không còn khớp tháng hiện tại.
        // Đây chính là chỗ gây bug: thiếu điều kiện này khiến qua tháng mới lại bị trả tiếp.
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
        }
        // Nếu chưa đủ tiền: không làm gì cả — người dùng có thể thêm thu nhập / giảm chi tiêu
        // rồi bấm refresh lại sau, vẫn trong tháng này thì vẫn hợp lệ để trả.
    }

    qDeleteAll(conLai);
    dongBoNguoiDungTuDatabase();
}
void AppController::datNguoiDungHienTai(int id) {
    // QUAN TRỌNG: KetNoiDatabase đã đổi sang file .db RIÊNG của tài khoản này rồi (xem
    // LoginController::dangNhap/dangKy — chạy TRƯỚC khi hàm này được gọi). File đó có thể
    // hoàn toàn trống (tài khoản mới) nên phải tạo lại bảng ở đây trước khi đọc/ghi gì cả.
    // taoBang() dùng CREATE TABLE IF NOT EXISTS nên gọi lại nhiều lần vẫn an toàn.
    ChiTieuRepository().taoBang();
    ThuNhapRepository().taoBang();
    MucTieuRepository().taoBang();

    // Nạp tên hiển thị / công việc theo tài khoản vừa đăng nhập.
    NguoiDungRepository ndRepo;
    NguoiDung nd = ndRepo.layThongTinTheoId(id);
    nguoiDungHienTai.setTen(nd.getTen());
    nguoiDungHienTai.setCongViec(nd.getCongViec());
    m_nguoiDungId = id;

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