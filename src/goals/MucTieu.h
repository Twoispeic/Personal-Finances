#ifndef MUCTIEUNGANHAN_H
#define MUCTIEUNGANHAN_H

#include "MucTieu.h"
#include "../patterns/TrangThaiMucTieu.h" // Nối với code của nhóm trưởng

class MucTieuNganHan : public MucTieu {
public:
    // Khởi tạo mục tiêu
    MucTieuNganHan(double mucTieu);

    // Các hàm xử lý
    void themTienTietKiem(double tienThem);

    // Đã đổi thành bool và thêm override cho khớp với class cha
    bool kiemTraHoanThanh() override;
};

#endif // MUCTIEUNGANHAN_H