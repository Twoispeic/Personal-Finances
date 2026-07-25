#ifndef TRANGTHAIDANGTHUCHIEN_H
#define TRANGTHAIDANGTHUCHIEN_H

#include "TrangThaiMucTieu.h"

class TrangThaiDangThucHien : public TrangThaiMucTieu {
public:
    QString layTenTrangThai() override {
        return "Dang thuc hien";
    }
};

#endif // TRANGTHAIDANGTHUCHIEN_H