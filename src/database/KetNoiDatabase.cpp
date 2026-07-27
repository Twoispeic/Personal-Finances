#include "KetNoiDatabase.h"

KetNoiDatabase& KetNoiDatabase::getInstance() {
    static KetNoiDatabase instance;
    return instance;
}

KetNoiDatabase::KetNoiDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("PersonalFinances.db");
}

KetNoiDatabase::~KetNoiDatabase() {
    dongKetNoi();
}

bool KetNoiDatabase::moKetNoi() {
    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "Loi ket noi Database:" << db.lastError().text();
            return false;
        }
    }
    return true;
}

void KetNoiDatabase::dongKetNoi() {
    if (db.isOpen()) {
        db.close();
    }
}

QSqlDatabase KetNoiDatabase::getDatabase() const {
    return db;
}