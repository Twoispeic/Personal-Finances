#ifndef KETNOIDATABASE_H
#define KETNOIDATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class KetNoiDatabase {
private:
    QSqlDatabase db;
    KetNoiDatabase(); // Sử dụng Singleton Pattern cho đồ án

public:
    static KetNoiDatabase& getInstance();
    bool moKetNoi();
    void dongKetNoi();
    void taoBangMacDinh();
};

#endif // KETNOIDATABASE_H