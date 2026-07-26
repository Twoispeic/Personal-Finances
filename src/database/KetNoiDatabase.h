#ifndef KETNOIDATABASE_H
#define KETNOIDATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>

class KetNoiDatabase {
private:
    QSqlDatabase db;

public:
    KetNoiDatabase();
    ~KetNoiDatabase();

    bool moKetNoi();
    void dongKetNoi();
    QSqlDatabase getDatabase() const;
};

#endif // KETNOIDATABASE_H