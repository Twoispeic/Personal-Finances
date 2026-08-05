#include "KetNoiDatabase.h"
#include <QStandardPaths>
#include <QDir>
#include <QtSql/QSqlQuery>
KetNoiDatabase& KetNoiDatabase::getInstance() {
    static KetNoiDatabase instance;
    return instance;
}

KetNoiDatabase::KetNoiDatabase() {
    QString thuMuc = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(thuMuc);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(thuMuc + "/PersonalFinances.db");
    qDebug() << "Duong dan Database:" << (thuMuc + "/PersonalFinances.db");
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
        QSqlQuery query(db);
        query.exec("PRAGMA foreign_keys = ON");
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