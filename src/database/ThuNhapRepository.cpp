#include "ThuNhapRepository.h"
#include"NgayMoPhong.h"
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

QList<ThuNhap> ThuNhapRepository::layThangHienTai() {
    QList<ThuNhap> ketQua;
    if (!KetNoiDatabase::getInstance().moKetNoi()) return ketQua;

    QString thangHienTai = NgayMoPhong::layNgayHienTai().toString("yyyy-MM");
    QSqlQuery query;
    query.prepare("SELECT loai, soTien, ngay FROM ThuNhap WHERE strftime('%Y-%m', ngay) = :thang");
    query.bindValue(":thang", thangHienTai);
    query.exec();

    while (query.next()) {
        QString loai = query.value("loai").toString();
        double soTien = query.value("soTien").toDouble();
        QDate ngay = QDate::fromString(query.value("ngay").toString(), Qt::ISODate);
        ketQua.append(ThuNhap(loai, soTien, ngay));
    }
    return ketQua;
}

bool ThuNhapRepository::luuThuNhapThang(double soTien) {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;

    QString thangHienTai = NgayMoPhong::layNgayHienTai().toString("yyyy-MM");

    QSqlQuery kiemTra;
    kiemTra.prepare("SELECT id FROM ThuNhap WHERE strftime('%Y-%m', ngay) = :thang");
    kiemTra.bindValue(":thang", thangHienTai);
    kiemTra.exec();

    QSqlQuery query;
    if (kiemTra.next()) {
        int id = kiemTra.value("id").toInt();
        query.prepare("UPDATE ThuNhap SET soTien = :soTien WHERE id = :id");
        query.bindValue(":id", id);
    } else {
        query.prepare("INSERT INTO ThuNhap (loai, soTien, ngay) VALUES ('Thu nhap thang', :soTien, :ngay)");
        query.bindValue(":ngay", NgayMoPhong::layNgayHienTai().toString(Qt::ISODate));
    }
    query.bindValue(":soTien", soTien);
    return query.exec();
}
//Xoa thang hien tai
bool ThuNhapRepository::xoaThangHienTai() {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;
    QString thangHienTai = NgayMoPhong::layNgayHienTai().toString("yyyy-MM");
    QSqlQuery query;
    query.prepare("DELETE FROM ThuNhap WHERE strftime('%Y-%m', ngay) = :thang");
    query.bindValue(":thang", thangHienTai);
    return query.exec();
}

bool ThuNhapRepository::xoaTatCa() {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;
    return QSqlQuery().exec("DELETE FROM ThuNhap");
}