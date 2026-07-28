#include "ThuNhapRepository.h"
#include "KetNoiDatabase.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

ThuNhapRepository::ThuNhapRepository() {}

bool ThuNhapRepository::taoBang() {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;

    QSqlQuery query;
    QString sql = "CREATE TABLE IF NOT EXISTS ThuNhap ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "loai TEXT, "
                  "soTien REAL, "
                  "ngay TEXT)";
    return query.exec(sql);
}

bool ThuNhapRepository::them(const ThuNhap &thuNhap) {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO ThuNhap (loai, soTien, ngay) VALUES (:loai, :soTien, :ngay)");
    query.bindValue(":loai", thuNhap.getLoai());
    query.bindValue(":soTien", thuNhap.getSoTien());
    query.bindValue(":ngay", thuNhap.getNgay().toString(Qt::ISODate));
    return query.exec();
}

QList<ThuNhap> ThuNhapRepository::layTatCa() {
    QList<ThuNhap> ketQua;
    if (!KetNoiDatabase::getInstance().moKetNoi()) return ketQua;

    QSqlQuery query("SELECT loai, soTien, ngay FROM ThuNhap");
    while (query.next()) {
        QString loai = query.value("loai").toString();
        double soTien = query.value("soTien").toDouble();
        QDate ngay = QDate::fromString(query.value("ngay").toString(), Qt::ISODate);
        ketQua.append(ThuNhap(loai, soTien, ngay));
    }
    return ketQua;
}