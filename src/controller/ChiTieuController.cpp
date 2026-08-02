#include "ChiTieuController.h"
#include "database/ChiTieuRepository.h"

ChiTieuController::ChiTieuController(NguoiDung* nd, QObject* parent)
    : QObject(parent), nguoiDung(nd)
{
    ChiTieuRepository().taoBang();
    taiLai();
}

QVariantList ChiTieuController::danhSach() const { return m_danhSach; }
QVariantList ChiTieuController::thongKeBieuDo() const { return m_thongKeBieuDo; }
QVariantList ChiTieuController::danhSachChuaXacDinh() const { return m_danhSachChuaXacDinh; }

void ChiTieuController::taiLai() {
    m_danhSach.clear();
    m_thongKeBieuDo.clear();
    m_danhSachChuaXacDinh.clear(); // Reset list mới

    ChiTieuRepository repo;
    const QList<ChiTieu> ds = repo.layTatCa(); // Thêm const để né cảnh báo của Qt

    double tongChiTieu = 0.0;

    // 1. Nạp danh sách chi tiết và phân loại
    for (const ChiTieu& ct : ds) {
        QVariantMap m;
        m["loai"] = (int)ct.getLoai();
        m["soTien"] = ct.getSoTien();
        m["ngay"] = ct.getNgay().toString("dd/MM/yyyy");

        m_danhSach.append(m);
        tongChiTieu += ct.getSoTien();

        // Tự động nhặt các khoản "Khác" đưa vào list chưa xác định
        if (ct.getLoai() == KHAC) {
            m_danhSachChuaXacDinh.append(m);
        }
    }

    // 2. Chuẩn bị dữ liệu cho Biểu đồ tròn
    QMap<LoaiChiTieu, double> tongTheoLoai = repo.tinhTongTheoLoai();
    for (auto it = tongTheoLoai.begin(); it != tongTheoLoai.end(); ++it) {
        QVariantMap m;
        m["loai"] = (int)it.key();
        m["tongTien"] = it.value();

        // Tính %, tránh lỗi chia cho 0
        double phanTram = (tongChiTieu > 0) ? (it.value() / tongChiTieu) * 100.0 : 0.0;
        m["phanTram"] = phanTram;

        m_thongKeBieuDo.append(m);
    }

    emit duLieuThayDoi();
}

void ChiTieuController::them(int loai, double soTien) {
    ChiTieuRepository().them(ChiTieu((LoaiChiTieu)loai, soTien, QDate::currentDate()));
    taiLai();
}

void ChiTieuController::locTheoLoai(int loai) {
    m_danhSach.clear();
    const QList<ChiTieu> ds = ChiTieuRepository().locTheoLoai((LoaiChiTieu)loai);
    for (const ChiTieu& ct : ds) {
        QVariantMap m;
        m["loai"] = (int)ct.getLoai();
        m["soTien"] = ct.getSoTien();
        m["ngay"] = ct.getNgay().toString("dd/MM/yyyy");
        m_danhSach.append(m);
    }
    emit duLieuThayDoi();
}

void ChiTieuController::locTatCa() {
    taiLai();
}