#include "ThuNhapController.h"
#include "database/ThuNhapRepository.h"

ThuNhapController::ThuNhapController(NguoiDung* nd, QObject* parent)
    : QObject(parent), nguoiDung(nd)
{
    ThuNhapRepository().taoBang();
}

void ThuNhapController::luuThang(double soTien) {
    ThuNhapRepository().luuThuNhapThang(soTien);
    emit duLieuThayDoi();
}