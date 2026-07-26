#include "NguoiDungRepository.h"

NguoiDungRepository::NguoiDungRepository(KetNoiDatabase &db) : dbConnection(db) {}

bool NguoiDungRepository::taoBang() {
    if (!dbConnection.moKetNoi()) return false;

    QSqlQuery query;
    QString sql = "CREATE TABLE IF NOT EXISTS NguoiDung ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "ten TEXT, "
                  "congViec TEXT)";
    return query.exec(sql);
}

bool NguoiDungRepository::luuNguoiDung(const NguoiDung &nguoiDung) {
    if (!dbConnection.moKetNoi()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO NguoiDung (ten, congViec) VALUES (:ten, :congViec)");
    query.bindValue(":ten", nguoiDung.getTen());
    query.bindValue(":congViec", nguoiDung.getCongViec());

    return query.exec();
}

NguoiDung NguoiDungRepository::layThongTinNguoiDung() {
    NguoiDung nd;
    if (!dbConnection.moKetNoi()) return nd;

    QSqlQuery query("SELECT ten, congViec FROM NguoiDung LIMIT 1");
    if (query.next()) {
        nd.setTen(query.value("ten").toString());
        nd.setCongViec(query.value("congViec").toString());
    }
    return nd;
}