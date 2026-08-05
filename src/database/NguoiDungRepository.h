#ifndef NGUOIDUNGREPOSITORY_H
#define NGUOIDUNGREPOSITORY_H

#include "models/NguoiDung.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

class NguoiDungRepository {
public:
    NguoiDungRepository();
    bool taoBang();
    bool luuNguoiDung(const NguoiDung &nguoiDung);
    NguoiDung layThongTinNguoiDung();

    // BỔ SUNG cho đăng nhập/đăng ký — KHÔNG đụng gì tới ChiTieu/ThuNhap/MucTieu,
    // dữ liệu tài chính vẫn dùng chung như cũ, chỉ thêm lớp xác thực + tên hiển thị theo id.
    int dangKy(const QString& taiKhoan, const QString& matKhau, const QString& ten);   // >0 = id mới, -1 = trùng tài khoản
    int dangNhap(const QString& taiKhoan, const QString& matKhau);                     // >0 = id, -1 = sai
    NguoiDung layThongTinTheoId(int id);
};

#endif // NGUOIDUNGREPOSITORY_H