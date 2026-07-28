#ifndef THUNHAPREPOSITORY_H
#define THUNHAPREPOSITORY_H

#include <QList>
#include "models/ThuNhap.h"

class ThuNhapRepository {
public:
    ThuNhapRepository();
    bool taoBang();
    bool them(const ThuNhap &thuNhap);
    QList<ThuNhap> layTatCa();
};

#endif // THUNHAPREPOSITORY_H