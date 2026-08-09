#include "KetNoiDatabase.h"
#include <QStandardPaths>
#include <QDir>
#include <QRegularExpression>
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

bool KetNoiDatabase::chuyenSangDuLieuTaiKhoan(const QString& taiKhoan) {
    QString thuMuc = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(thuMuc);

    // Làm sạch tên tài khoản để dùng an toàn làm tên file (chỉ giữ chữ/số/_ . -)
    QString tenAnToan = taiKhoan;
    tenAnToan.replace(QRegularExpression("[^A-Za-z0-9_.-]"), "_");
    if (tenAnToan.isEmpty()) tenAnToan = "user";

    QString duongDanMoi = thuMuc + "/PersonalFinances_" + tenAnToan + ".db";

    // Đã đang mở đúng file của tài khoản này rồi thì thôi, khỏi đóng/mở lại
    if (db.isOpen() && db.databaseName() == duongDanMoi) return true;

    dongKetNoi();
    db.setDatabaseName(duongDanMoi);
    qDebug() << "Da chuyen Database (mac dinh) sang tai khoan:" << duongDanMoi;

    return moKetNoi();
}

QSqlDatabase KetNoiDatabase::moKetNoiTaiKhoan() {
    const QString tenConnection = "conn_taikhoan";

    QSqlDatabase dbTK;
    if (QSqlDatabase::contains(tenConnection)) {
        dbTK = QSqlDatabase::database(tenConnection);
    } else {
        QString thuMuc = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir().mkpath(thuMuc);
        dbTK = QSqlDatabase::addDatabase("QSQLITE", tenConnection);
        dbTK.setDatabaseName(thuMuc + "/TaiKhoan.db");   // 1 file DUY NHẤT, cố định, chỉ chứa bảng NguoiDung
    }
    if (!dbTK.isOpen() && !dbTK.open()) {
        qDebug() << "Loi ket noi Database tai khoan:" << dbTK.lastError().text();
    }
    return dbTK;
}