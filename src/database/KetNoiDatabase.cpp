#include "KetNoiDatabase.h"

KetNoiDatabase::KetNoiDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("QuanLyTaiChinh.db");
}

KetNoiDatabase& KetNoiDatabase::getInstance() {
    static KetNoiDatabase instance;
    return instance;
}

bool KetNoiDatabase::moKetNoi() {
    if (!db.open()) {
        qDebug() << "Loi ket noi:" << db.lastError().text();
        return false;
    }
    return true;
}

void KetNoiDatabase::dongKetNoi() {
    db.close();
}

void KetNoiDatabase::taoBangMacDinh() {
    if (moKetNoi()) {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS NguoiDung ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "ten TEXT, "
                   "congViec TEXT)");
        dongKetNoi();
    }
}