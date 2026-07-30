#include "ChiTieuRepository.h"
#include "KetNoiDatabase.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

ChiTieuRepository::ChiTieuRepository() {}

QString ChiTieuRepository::loaiSangText(LoaiChiTieu loai) const {
    switch (loai) {
    case TIEN_SINH_HOAT: return "TIEN_SINH_HOAT";
    case TIEN_DIEN_NUOC: return "TIEN_DIEN_NUOC";
    case TIEN_NHA:        return "TIEN_NHA";
    default:               return "KHAC";
    }
}

LoaiChiTieu ChiTieuRepository::textSangLoai(const QString &text) const {
    if (text == "TIEN_SINH_HOAT") return TIEN_SINH_HOAT;
    if (text == "TIEN_DIEN_NUOC") return TIEN_DIEN_NUOC;
    if (text == "TIEN_NHA") return TIEN_NHA;
    return KHAC;
}

bool ChiTieuRepository::taoBang() {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;

    QSqlQuery query;
    QString sql = "CREATE TABLE IF NOT EXISTS ChiTieu ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "loai TEXT, "
                  "soTien REAL, "
                  "ngay TEXT)";
    return query.exec(sql);
}

bool ChiTieuRepository::them(const ChiTieu &chiTieu) {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO ChiTieu (loai, soTien, ngay) VALUES (:loai, :soTien, :ngay)");
    query.bindValue(":loai", loaiSangText(chiTieu.getLoai()));
    query.bindValue(":soTien", chiTieu.getSoTien());
    query.bindValue(":ngay", chiTieu.getNgay().toString(Qt::ISODate));
    return query.exec();
}

QList<ChiTieu> ChiTieuRepository::layTatCa() {
    QList<ChiTieu> ketQua;
    if (!KetNoiDatabase::getInstance().moKetNoi()) return ketQua;

    QSqlQuery query("SELECT loai, soTien, ngay FROM ChiTieu");
    while (query.next()) {
        LoaiChiTieu loai = textSangLoai(query.value("loai").toString());
        double soTien = query.value("soTien").toDouble();
        QDate ngay = QDate::fromString(query.value("ngay").toString(), Qt::ISODate);
        ketQua.append(ChiTieu(loai, soTien, ngay));
    }
    return ketQua;
}


QMap<LoaiChiTieu, double> ChiTieuRepository::tinhTongTheoLoai() {
    QMap<LoaiChiTieu, double> ketQua;
    ketQua[TIEN_SINH_HOAT] = 0;
    ketQua[TIEN_DIEN_NUOC] = 0;
    ketQua[TIEN_NHA] = 0;
    ketQua[KHAC] = 0;

    for (const ChiTieu &ct : layTatCa()) {
        ketQua[ct.getLoai()] += ct.getSoTien();
    }
    return ketQua;
}

// ChiTieuRepository.cpp
QList<ChiTieu> ChiTieuRepository::locTheoLoai(LoaiChiTieu loai) {
    QList<ChiTieu> ketQua;
    if (!KetNoiDatabase::getInstance().moKetNoi()) return ketQua;

    QSqlQuery query;
    query.prepare("SELECT loai, soTien, ngay FROM ChiTieu WHERE loai = :loai");
    query.bindValue(":loai", loaiSangText(loai));
    query.exec();

    while (query.next()) {
        double soTien = query.value("soTien").toDouble();
        QDate ngay = QDate::fromString(query.value("ngay").toString(), Qt::ISODate);
        ketQua.append(ChiTieu(loai, soTien, ngay));
    }
    return ketQua;
}

QList<ChiTieu> ChiTieuRepository::locTheoKhoangThoiGian(const QDate& tuNgay, const QDate& denNgay) {
    QList<ChiTieu> ketQua;
    if (!KetNoiDatabase::getInstance().moKetNoi()) return ketQua;

    QSqlQuery query;
    query.prepare("SELECT loai, soTien, ngay FROM ChiTieu WHERE ngay BETWEEN :tu AND :den");
    query.bindValue(":tu", tuNgay.toString(Qt::ISODate));
    query.bindValue(":den", denNgay.toString(Qt::ISODate));
    query.exec();

    while (query.next()) {
        LoaiChiTieu loai = textSangLoai(query.value("loai").toString());
        double soTien = query.value("soTien").toDouble();
        QDate ngay = QDate::fromString(query.value("ngay").toString(), Qt::ISODate);
        ketQua.append(ChiTieu(loai, soTien, ngay));
    }
    return ketQua;
}
