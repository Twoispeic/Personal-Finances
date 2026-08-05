// .cpp
#include "NgayMoPhong.h"
#include <QSettings>

// id = 0 nghĩa là "chưa đăng nhập tài khoản nào" (fallback an toàn, không vỡ code cũ).
// Mỗi tài khoản có id riêng (AUTOINCREMENT, không bao giờ trùng/tái sử dụng) nên dùng id
// làm hậu tố key là đủ để đảm bảo tài khoản mới KHÔNG đọc nhầm tháng mô phỏng của tài khoản khác.
static int s_idTaiKhoanHienTai = 0;

static QString khoaThangMoPhong() {
    return QString("ThangMoPhongHienTai_%1").arg(s_idTaiKhoanHienTai);
}

void NgayMoPhong::datTaiKhoanHienTai(int idNguoiDung) {
    s_idTaiKhoanHienTai = idNguoiDung;
}

QDate NgayMoPhong::layNgayHienTai() {
    QSettings s("MyApp", "TaiChinh");
    QString khoa = khoaThangMoPhong();
    QString luu = s.value(khoa, "").toString();
    if (luu.isEmpty()) {
        QDate d(QDate::currentDate().year(), QDate::currentDate().month(), 1);
        s.setValue(khoa, d.toString("yyyy-MM-dd"));
        return d;
    }
    return QDate::fromString(luu, "yyyy-MM-dd");
}
QDate NgayMoPhong::quaThangMoi() {
    QDate moi = layNgayHienTai().addMonths(1);
    QSettings("MyApp", "TaiChinh").setValue(khoaThangMoPhong(), moi.toString("yyyy-MM-dd"));
    return moi;
}