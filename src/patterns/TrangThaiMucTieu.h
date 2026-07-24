#ifndef TRANGTHAIMUCTIEU_H
#define TRANGTHAIMUCTIEU_H
#include <Qstring>
//state pattern
class MucTieu;
class TrangThaiMucTieu{
public:
    virtual ~TrangThaiMucTieu(){}
    virtual QString layMauSac()const=0;
    virtual void kiemTraChuyen(MucTieu *muctieu)=0;
};

#endif // TRANGTHAIMUCTIEU_H
