// .h
#ifndef NGAYMOPHONG_H
#define NGAYMOPHONG_H
#include <QDate>
class NgayMoPhong {
public:
    static void datTaiKhoanHienTai(int idNguoiDung);
    static QDate layNgayHienTai();
    static QDate quaThangMoi();
};
#endif