#ifndef TRANGTHAICHUAXONG_H
#define TRANGTHAICHUAXONG_H
#include"TrangThaiMucTieu.h"
class TrangThaiChuaXong:public TrangThaiMucTieu
{
public:
    QString layMauSac() const override;
    void kiemTraChuyen(MucTieu* mucTieu) override;
};

#endif // TRANGTHAICHUAXONG_H
