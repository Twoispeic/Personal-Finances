#ifndef MUCTIEUREPOSITORY_H
#define MUCTIEUREPOSITORY_H

#include <QList>
#include "goals/MucTieu.h"

class MucTieuRepository {
public:
    MucTieuRepository();
    bool taoBang();
    bool them(MucTieu* mucTieu);
    bool capNhatTienDaTietKiem(int id, double soTienMoi);
    QList<MucTieu*> layTatCa();
};

#endif // MUCTIEUREPOSITORY_H