#ifndef THUNHAPREPOSITORY_H
#define THUNHAPREPOSITORY_H

#include <QList>
#include "models/ThuNhap.h"

class ThuNhapRepository {
public:
    ThuNhapRepository();
    bool taoBang();
    bool them(const ThuNhap &thuNhap);
    QList<ThuNhap> layTatCa();          // TOÀN BỘ lịch sử — dùng cho biểu đồ 12 tháng
    QList<ThuNhap> layThangHienTai();   // CHỈ tháng hiện tại — dùng để tính thu/chi/số dư
    bool luuThuNhapThang(double soTien);
    bool xoaThangHienTai();
    bool xoaTatCa();
};

#endif // THUNHAPREPOSITORY_H