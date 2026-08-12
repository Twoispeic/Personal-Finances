// .cpp
#include "NgayMoPhong.h"
#include <QSettings>

NgayMoPhong& NgayMoPhong::getInstance() {
    static NgayMoPhong instance;   // tạo đúng 1 lần, lần gọi getInstance() đầu tiên; sống tới khi app thoát
    return instance;
}

QString NgayMoPhong::khoaThangMoPhong() const {
    return QString("ThangMoPhongHienTai_%1").arg(idTaiKhoanHienTai);
}

void NgayMoPhong::datTaiKhoanHienTai(int idNguoiDung) {
    idTaiKhoanHienTai = idNguoiDung;
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