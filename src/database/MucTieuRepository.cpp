#include "MucTieuRepository.h"
#include "KetNoiDatabase.h"
#include "src/goals/MucTieuNganHan.h"
#include "src/goals/MucTieuDaiHan.h"
#include "src/goals/MucTieuFactory.h"
#include "src/patterns/TrangThaiChuaXong.h"
#include "src/patterns/TrangThaiHoanThanh.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

MucTieuRepository::MucTieuRepository() {}

bool MucTieuRepository::taoBang() {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;

    QSqlQuery query;
    QString sql = "CREATE TABLE IF NOT EXISTS MucTieu ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "loaiMucTieu TEXT, "
                  "tenMucTieu TEXT, "
                  "soTienMucTieu REAL, "
                  "soTienDaTietKiem REAL, "
                  "trangThai TEXT, "
                  "thoiHanThang INTEGER, "
                  "soKyTraGop INTEGER, "
                  "soTienMoiKy REAL)";
    return query.exec(sql);
}

bool MucTieuRepository::them(MucTieu* mucTieu) {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;

    QSqlQuery query;
    MucTieuNganHan* ngan = dynamic_cast<MucTieuNganHan*>(mucTieu);
    MucTieuDaiHan* dai = dynamic_cast<MucTieuDaiHan*>(mucTieu);

    query.prepare("INSERT INTO MucTieu "
                  "(loaiMucTieu, tenMucTieu, soTienMucTieu, soTienDaTietKiem, trangThai, thoiHanThang, soKyTraGop, soTienMoiKy) "
                  "VALUES (:loai, :ten, :soTienMT, :soTienDTK, :trangThai, :thoiHan, :soKy, :soTienKy)");

    query.bindValue(":ten", mucTieu->getTenMucTieu());
    query.bindValue(":soTienMT", mucTieu->getSoTienMucTieu());
    query.bindValue(":soTienDTK", mucTieu->getSoTienDaTietKiem());
    query.bindValue(":trangThai", mucTieu->layMauSacHienTai() == "green" ? "HoanThanh" : "ChuaXong");

    if (ngan != nullptr) {
        query.bindValue(":loai", "NganHan");
        query.bindValue(":thoiHan", ngan->getThoiHanThang());
        query.bindValue(":soKy", QVariant());
        query.bindValue(":soTienKy", QVariant());
    } else if (dai != nullptr) {
        query.bindValue(":loai", "DaiHan");
        query.bindValue(":thoiHan", QVariant());
        query.bindValue(":soKy", dai->getSoKyTraGop());
        query.bindValue(":soTienKy", dai->getSoTienMoiKy());
    }

    return query.exec();
}

bool MucTieuRepository::capNhatTienDaTietKiem(int id, double soTienMoi) {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;

    QSqlQuery query;
    query.prepare("UPDATE MucTieu SET soTienDaTietKiem = :soTien WHERE id = :id");
    query.bindValue(":soTien", soTienMoi);
    query.bindValue(":id", id);
    return query.exec();
}

QList<MucTieu*> MucTieuRepository::layTatCa() {
    QList<MucTieu*> ketQua;
    if (!KetNoiDatabase::getInstance().moKetNoi()) return ketQua;

    QSqlQuery query("SELECT loaiMucTieu, tenMucTieu, soTienMucTieu, soTienDaTietKiem, "
                    "trangThai, thoiHanThang, soKyTraGop, soTienMoiKy FROM MucTieu");

    while (query.next()) {
        QString loai = query.value("loaiMucTieu").toString();
        QString ten = query.value("tenMucTieu").toString();
        double soTienMT = query.value("soTienMucTieu").toDouble();
        double soTienDTK = query.value("soTienDaTietKiem").toDouble();
        QString trangThai = query.value("trangThai").toString();

        MucTieu* mt = nullptr;
        if (loai == "NganHan") {
            int thoiHan = query.value("thoiHanThang").toInt();
            mt = MucTieuFactory::taoMucTieuNganHan(ten, soTienMT, thoiHan);
        } else {
            int soKy = query.value("soKyTraGop").toInt();
            mt = MucTieuFactory::taoMucTieuDaiHan(ten, soTienMT, soKy);
        }

        mt->datSoTienDaTietKiem(soTienDTK);   // nạp lại tiến độ, không tính lại qua Strategy
        if (trangThai == "HoanThanh") {
            mt->datTrangThai(new TrangThaiHoanThanh());
        } else {
            mt->datTrangThai(new TrangThaiChuaXong());
        }

        ketQua.append(mt);
    }
    return ketQua;
}