#ifndef TRANGTHAIMUCTIEU_H
#define TRANGTHAIMUCTIEU_H

#include <QString>

// Đây là Interface cho Design Pattern State
class TrangThaiMucTieu {
public:
    virtual ~TrangThaiMucTieu() {}

    // Hàm thuần ảo: Trả về tên của trạng thái
    virtual QString layTenTrangThai() = 0;
};

#endif // TRANGTHAIMUCTIEU_H