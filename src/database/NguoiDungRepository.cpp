#include "NguoiDungRepository.h"
#include "KetNoiDatabase.h"
NguoiDungRepository::NguoiDungRepository() {}

bool NguoiDungRepository::taoBang() {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;

    QSqlQuery query;
    QString sql = "CREATE TABLE IF NOT EXISTS NguoiDung ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "ten TEXT, "
                  "congViec TEXT)";
    return query.exec(sql);
}

bool NguoiDungRepository::luuNguoiDung(const NguoiDung &nguoiDung) {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;

    QSqlQuery kiemTra;
    kiemTra.exec("SELECT COUNT(*) FROM NguoiDung");
    kiemTra.next();
    bool daCoDuLieu = kiemTra.value(0).toInt() > 0;

    QSqlQuery query;
    if (daCoDuLieu) {
        query.prepare("UPDATE NguoiDung SET ten = :ten, congViec = :congViec WHERE id = 1");
    } else {
        query.prepare("INSERT INTO NguoiDung (ten, congViec) VALUES (:ten, :congViec)");
    }
    query.bindValue(":ten", nguoiDung.getTen());
    query.bindValue(":congViec", nguoiDung.getCongViec());
    return query.exec();
}

NguoiDung NguoiDungRepository::layThongTinNguoiDung() {
    NguoiDung nd;
    if (!KetNoiDatabase::getInstance().moKetNoi()) return nd;

    QSqlQuery query("SELECT ten, congViec FROM NguoiDung LIMIT 1");
    if (query.next()) {
        nd.setTen(query.value("ten").toString());
        nd.setCongViec(query.value("congViec").toString());
    }
    return nd;
}