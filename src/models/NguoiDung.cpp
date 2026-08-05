#include "NguoiDung.h"
#include"src/goals/MucTieuFactory.h"
#include "goals/MucTieuNganHan.h"
#include "goals/MucTieuDaiHan.h"
NguoiDung::NguoiDung() : ten(""), congViec("") {}

NguoiDung::NguoiDung(QString ten, QString congViec)
    : ten(ten), congViec(congViec) {}

NguoiDung::~NguoiDung() {
    qDeleteAll(danhSachMucTieu);
}

QString NguoiDung::getTen() const { return ten; }
void NguoiDung::setTen(const QString &ten) { this->ten = ten; }

QString NguoiDung::getCongViec() const { return congViec; }
void NguoiDung::setCongViec(const QString &congViec) { this->congViec = congViec; }

void NguoiDung::themThuNhap(const ThuNhap &thuNhap) {
    danhSachThuNhap.append(thuNhap);
}

void NguoiDung::themChiTieu(const ChiTieu &chiTieu) {
    danhSachChiTieu.append(chiTieu);
}

MucTieu* NguoiDung::taoMucTieuNganHan(const QString& ten, double soTienMucTieu, int thoiHanThang) {
    MucTieu* mt = MucTieuFactory::taoMucTieuNganHan(ten, soTienMucTieu, thoiHanThang);
    danhSachMucTieu.append(mt);
    return mt;
}

MucTieu* NguoiDung::taoMucTieuDaiHan(const QString& ten, double soTienMucTieu, int soKyTraGop) {
    MucTieu* mt = MucTieuFactory::taoMucTieuDaiHan(ten, soTienMucTieu, soKyTraGop);
    danhSachMucTieu.append(mt);
    return mt;
}

double NguoiDung::tinhTongThuNhap() const {
    double tong = 0;
    for (const auto &tn : danhSachThuNhap) {
        tong += tn.getSoTien();
    }
    return tong;
}

double NguoiDung::tinhTongChiTieu() const {
    double tong = 0;
    for (const auto &ct : danhSachChiTieu) {
        tong += ct.getSoTien();
    }
    return tong;
}

double NguoiDung::tinhSoDuThang() const {
    return tinhTongThuNhap() - tinhTongChiTieu();
}

double NguoiDung::phanBoTienTietKiem() {
    double conLai = tinhSoDuThang();
    if (conLai <= 0) return 0.0;

    // Dài hạn — luôn bắt buộc, tự động chạy
    for (MucTieu* const &mt : danhSachMucTieu) {
        if (dynamic_cast<MucTieuDaiHan*>(mt) != nullptr) {
            conLai -= mt->capNhatTietKiem(conLai);
            if (conLai <= 0) break;
        }
    }

    return conLai;   // trả về phần còn dư, để GUI hỏi có muốn góp ngắn hạn không
}

double NguoiDung::phanBoTienTietKiem(double soTienKhaDung) {
    double conLai = soTienKhaDung;
    if (conLai <= 0) return 0.0;

    // Dài hạn — luôn bắt buộc, tự động chạy
    for (MucTieu* const &mt : danhSachMucTieu) {
        if (dynamic_cast<MucTieuDaiHan*>(mt) != nullptr) {
            conLai -= mt->capNhatTietKiem(conLai);
            if (conLai <= 0) break;
        }
    }

    return conLai;   // trả về phần còn dư
}

double NguoiDung::gopTietKiemNganHan(MucTieu* mt, double soTien) {
    if (mt == nullptr || soTien <= 0) return 0.0;
    if (dynamic_cast<MucTieuNganHan*>(mt) == nullptr) return 0.0;

    // capNhatTietKiem() trả về số tiền THỰC SỰ được dùng (đã tự cắt bớt nếu soTien vượt
    // quá phần còn thiếu của mục tiêu) — phải trả đúng số này ra ngoài, KHÔNG trả nguyên
    // soTien gốc, để nơi gọi (MucTieuController::gop) trừ đúng số đó khỏi hũ tiết kiệm.
    return mt->capNhatTietKiem(soTien);
}

// demo conclude
void NguoiDung::ketThucThang() {
    phanBoTienTietKiem();   // phân bổ tiền dư theo đúng logic đã có

    // "Đóng sổ" tháng: xoá buffer trong RAM, vì dữ liệu thật đã lưu xuống DB rồi
    danhSachThuNhap.clear();
    danhSachChiTieu.clear();
}

// Thu nhap
void NguoiDung::xoaDanhSachThuNhap() { danhSachThuNhap.clear(); }
void NguoiDung::xoaDanhSachChiTieu() { danhSachChiTieu.clear(); }
//Muc tieu
void NguoiDung::xoaDanhSachMucTieu() {
    qDeleteAll(danhSachMucTieu);
    danhSachMucTieu.clear();
}
void NguoiDung::themMucTieuVaoDanhSach(MucTieu* mt) {
    danhSachMucTieu.append(mt);
}

const QList<MucTieu*>& NguoiDung::layDanhSachMucTieu() const { return danhSachMucTieu; }