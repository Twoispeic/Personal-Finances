#ifndef MUCTIEUREPOSITORY_H
#define MUCTIEUREPOSITORY_H

#include <QList>
#include "src/goals/MucTieu.h"

class MucTieuRepository {
public:
    MucTieuRepository();
    bool taoBang();

    // Đã thêm int nguoiDungId
    bool them(MucTieu* mucTieu);
    bool capNhatTienDaTietKiem(int id, double soTienMoi);
    QList<MucTieu*> layTatCa();
    bool xoa(int id);
    bool capNhatTrangThaiThang(int id, double soTienDaTietKiemMoi, int soKyDaTraMoi, const QString& thangNamDaTraMoi, double soTienMocAnToanMoi);
};

#endif // MUCTIEUREPOSITORY_H