#include "ThuNhapController.h"
#include "database/ThuNhapRepository.h"
#include "database/MucTieuRepository.h"
#include <QDate>
#include <QMap>

ThuNhapController::ThuNhapController(NguoiDung* nd, QObject* parent)
    : QObject(parent), nguoiDung(nd)
{
    ThuNhapRepository().taoBang();
    taiLai();
}

QVariantList ThuNhapController::thongKe12Thang() const { return m_thongKe12Thang; }
double ThuNhapController::tongThuNhap12Thang() const { return m_tongThuNhap12Thang; }
double ThuNhapController::tongTienTietKiem() const { return m_tongTienTietKiem; }

void ThuNhapController::taiLai() {
    m_thongKe12Thang.clear();
    m_tongThuNhap12Thang = 0.0;
    m_tongTienTietKiem = 0.0;

    QDate thoiDiemHienTai = QDate::currentDate();

    // 1. Tạo danh sách 12 tháng gần nhất (để đảm bảo biểu đồ không bị thiếu cột tháng nào)
    QMap<QString, double> banDoThuNhap;
    QList<QString> thuTuThang; // Lưu thứ tự để parse vào QVariantList không bị lộn xộn

    for (int i = 11; i >= 0; --i) {
        QDate thangLui = thoiDiemHienTai.addMonths(-i);
        QString keyThang = thangLui.toString("MM/yyyy");
        banDoThuNhap[keyThang] = 0.0;
        thuTuThang.append(keyThang);
    }

    // 2. Lấy toàn bộ Thu Nhập và cộng dồn vào tháng tương ứng
    ThuNhapRepository repoThuNhap;
    const QList<ThuNhap> dsThuNhap = repoThuNhap.layTatCa();

    for (const ThuNhap& tn : dsThuNhap) {
        QString keyThang = tn.getNgay().toString("MM/yyyy");

        // Nếu khoảng thời gian của khoản thu nhập nằm trong 12 tháng gần nhất
        if (banDoThuNhap.contains(keyThang)) {
            banDoThuNhap[keyThang] += tn.getSoTien();
            m_tongThuNhap12Thang += tn.getSoTien();
        }
    }

    // 3. Đưa vào QVariantList để QML dùng cho BarChart
    for (const QString& key : thuTuThang) {
        QVariantMap m;
        m["thang"] = key; // Trục X
        m["soTien"] = banDoThuNhap[key]; // Trục Y
        m_thongKe12Thang.append(m);
    }

    // 4. Tính tổng tiền tiết kiệm từ tất cả Mục Tiêu Tài Chính
    MucTieuRepository repoMucTieu;
    const QList<MucTieu*> dsMucTieu = repoMucTieu.layTatCa();
    for (MucTieu* mt : dsMucTieu) {
        m_tongTienTietKiem += mt->getSoTienDaTietKiem();
    }
    qDeleteAll(dsMucTieu); // Tránh rò rỉ bộ nhớ

    emit duLieuThayDoi();
}

void ThuNhapController::luuThang(double soTien) {
    ThuNhapRepository().luuThuNhapThang(soTien);
    // Lưu xong thì gọi taiLai() để cập nhật ngay biểu đồ và các con số
    taiLai();
}