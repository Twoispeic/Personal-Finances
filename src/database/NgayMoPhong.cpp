// .cpp
#include "NgayMoPhong.h"
#include <QSettings>
static const char* KHOA = "ThangMoPhongHienTai";
QDate NgayMoPhong::layNgayHienTai() {
    QSettings s("MyApp", "TaiChinh");
    QString luu = s.value(KHOA, "").toString();
    if (luu.isEmpty()) {
        QDate d(QDate::currentDate().year(), QDate::currentDate().month(), 1);
        s.setValue(KHOA, d.toString("yyyy-MM-dd"));
        return d;
    }
    return QDate::fromString(luu, "yyyy-MM-dd");
}
QDate NgayMoPhong::quaThangMoi() {
    QDate moi = layNgayHienTai().addMonths(1);
    QSettings("MyApp", "TaiChinh").setValue(KHOA, moi.toString("yyyy-MM-dd"));
    return moi;
}