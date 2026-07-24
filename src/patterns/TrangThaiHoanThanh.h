#ifndef TRANGTHAIHOANTHANH_H
#define TRANGTHAIHOANTHANH_H

#include "TrangThaiMucTieu.h"

class TrangThaiHoanThanh : public TrangThaiMucTieu
{
public:
    QString layMauSac() const override;
    void kiemTraChuyen(MucTieu *muctieu) override;
};

#endif // TRANGTHAIHOANTHANH_H
