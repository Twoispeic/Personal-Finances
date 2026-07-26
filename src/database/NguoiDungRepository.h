#ifndef NGUOIDUNGREPOSITORY_H
#define NGUOIDUNGREPOSITORY_H

#include "models/NguoiDung.h"
#include "KetNoiDatabase.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

class NguoiDungRepository {
private:
    KetNoiDatabase &dbConnection;

public:
    NguoiDungRepository(KetNoiDatabase &db);

    bool taoBang();
    bool luuNguoiDung(const NguoiDung &nguoiDung);
    NguoiDung layThongTinNguoiDung();
};

#endif // NGUOIDUNGREPOSITORY_H