#include "TrangThaiChuaXong.h"
#include "TrangThaiHoanThanh.h"
#include "src/goals/MucTieu.h"   // .cpp thì include thoải mái, không sợ vòng nữa

QString TrangThaiChuaXong::layMauSac() const {
    return "red";
}

void TrangThaiChuaXong::kiemTraChuyen(MucTieu* mucTieu) {
    if (mucTieu->tinhTienDoPhanTram() >= 100.0) {
        mucTieu->datTrangThai(new TrangThaiHoanThanh());
    }
}
