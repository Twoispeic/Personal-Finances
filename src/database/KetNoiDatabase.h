#ifndef KETNOIDATABASE_H
#define KETNOIDATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
//Singleton
class KetNoiDatabase {
private:
    QSqlDatabase db;

    KetNoiDatabase();
    ~KetNoiDatabase();

    KetNoiDatabase(const KetNoiDatabase&) = delete;
    KetNoiDatabase& operator=(const KetNoiDatabase&) = delete;

public:
    // Phương thức tĩnh lấy instance duy nhất
    static KetNoiDatabase& getInstance();

    bool moKetNoi();
    void dongKetNoi();
    QSqlDatabase getDatabase() const;
};

#endif // KETNOIDATABASE_H