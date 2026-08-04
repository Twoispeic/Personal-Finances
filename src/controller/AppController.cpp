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
    QSettings settings("MyApp", "TaiChinh");
    QString thangNamHienTai = QDate::currentDate().toString("yyyy-MM");
    QString thangDaChotSo = settings.value("ThangDaChotSo", "").toString();

    // Khoá: 1 tháng chỉ chốt sổ 1 lần. Bấm lại trong cùng tháng (vd. bấm nhầm 2 lần) sẽ KHÔNG
    // cộng dồn số dư luỹ kế lần nữa — tránh cộng trùng tiền vì ThuNhap tháng này không bị xoá.
    if (thangDaChotSo == thangNamHienTai) {
        return huTietKiem();
    }

    // Trả góp dài hạn tháng này nếu CHƯA được trả (vd. người dùng chưa từng bấm refresh tháng này).
    // Nếu đã trả rồi (do bấm refresh trước đó) thì hàm này sẽ tự bỏ qua — không trả trùng.
    traGopMucTieuDaiHanThangNay();

    // QUAN TRỌNG: phải làm mới cache của m_mucTieu NGAY sau khi trả góp, để huTietKiem() bên dưới
    // tính đúng phần tiền vừa bị trừ đi cho mục tiêu dài hạn (tránh lưu dư số dư luỹ kế).
    m_mucTieu->taiLai();

    // Lưu phần dư còn lại làm gốc cho tháng sau
    settings.setValue("SoDuLuyKe", huTietKiem());
    settings.setValue("ThangDaChotSo", thangNamHienTai);
    // Ghi nhớ phần thu nhập ĐÃ được gộp vào SoDuLuyKe ở trên — vì ThuNhap của tháng này
    // không bị xoá nữa (để giữ biểu đồ), nên phải trừ lại phần này ra khi tính huTietKiem()
    // trong những lần gọi sau, tránh bị cộng dư (double count) cho tới khi sang tháng thật mới.
    settings.setValue("ThuNhapDaTinhLuyKe", tongThuNhap());

    // CHỈ xoá Chi Tiêu tháng này để bắt đầu tháng mới (ChiTieu không cần giữ lịch sử).
    // KHÔNG xoá ThuNhap nữa: mỗi tháng chỉ có đúng 1 dòng (do luuThang() upsert theo tháng),
    // xoá đi sẽ làm mất luôn dữ liệu biểu đồ 12 tháng ở trang Thu Nhập.
    ChiTieuRepository().xoaTatCa();

    dongBoNguoiDungTuDatabase();
    m_thuNhap->taiLai();
    emit duLieuThayDoi();
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
    double luyKe = settings.value("SoDuLuyKe", 0.0).toDouble();

    QString thangNamHienTai = QDate::currentDate().toString("yyyy-MM");
    QString thangDaChotSo = settings.value("ThangDaChotSo", "").toString();

    // Vẫn giữ biến này để tránh cộng trùng thu nhập nếu chốt sổ xong vẫn ở nguyên tháng đó
    double thuNhapDaTinh = (thangDaChotSo == thangNamHienTai)
                               ? settings.value("ThuNhapDaTinhLuyKe", 0.0).toDouble()
                               : 0.0;

    // KHÔNG CẦN trừ tongDaTietKiem() nữa
    double con = luyKe + (soDuThang() - thuNhapDaTinh);
    return con > 0 ? con : 0;
}

// ==========================================================================
// Xác nhận HOÀN THÀNH 1 mục tiêu (áp dụng cho cả Ngắn Hạn lẫn Dài Hạn) và xoá nó khỏi danh sách.
// KHÔNG trả tiền về hũ tiết kiệm khả dụng — số tiền đã tiết kiệm được coi như đã dùng đúng mục
// đích của mục tiêu (mua đồ, hoàn thành kế hoạch...), không phải huỷ bỏ giữa chừng.
//
// Vì huTietKiem() = luyKe + soDuThang() - tongDaTietKiem(), nếu chỉ xoá mục tiêu (làm
// tongDaTietKiem() giảm đi) mà không xử lý gì thêm, số tiền đó sẽ tự động "hiện ra" lại trong
// hũ khả dụng — coi như được hoàn tiền, điều KHÔNG mong muốn ở đây. Để bù trừ, ta trừ đúng số
// tiền đã tiết kiệm của mục tiêu này ra khỏi SoDuLuyKe, giữ cho huTietKiem() không đổi sau khi xoá.
// ==========================================================================
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

// ==========================================================================
// Trả góp mục tiêu dài hạn cho THÁNG HIỆN TẠI.
// - Đọc thẳng từ DB (không dùng biến static trong RAM) để trạng thái "đã trả tháng này chưa"
//   luôn đúng kể cả sau khi tắt/mở lại app.
// - Idempotent: bấm refresh (hoặc chốt sổ) bao nhiêu lần trong tháng cũng chỉ trả ĐÚNG 1 LẦN
//   cho mỗi mục tiêu — vì mỗi mục tiêu tự nhớ "thangNamDaTra" của lần trả gần nhất.
// - Fail-safe: nếu hũ tiền (soTienDaTietKiem) của 1 mục tiêu ĐÃ TỪNG CÓ TIẾN ĐỘ (soTienMocAnToan > 0)
//   bỗng dưng thấp hơn mốc an toàn đã ghi nhận lần trả gần nhất -> dữ liệu bất thường (bị sửa tay,
//   đồng bộ lỗi...) -> xoá mục tiêu đó để người dùng biết mà tạo lại, tránh tính toán sai dây chuyền.
// ==========================================================================
void AppController::traGopMucTieuDaiHanThangNay() {
    MucTieuRepository repo;
    QString thangNamHienTai = QDate::currentDate().toString("yyyy-MM");

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

        double tienCanTra = mt->getSoTienMoiKy();
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