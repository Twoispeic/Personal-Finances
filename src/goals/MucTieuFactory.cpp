#include "MucTieuFactory.h"
#include "MucTieu.h"
#include "MucTieuNganHan.h"
#include "MucTieuDaiHan.h"
#include "src/patterns/ChienLuocNganHan.h"
#include "src/patterns/ChienLuocDaiHan.h"
#include "src/patterns/TrangThaiChuaXong.h"

MucTieu* MucTieuFactory::taoMucTieuNganHan(const QString& ten, double soTienMucTieu, int thoiHanThang) {
    MucTieu* mt = new MucTieuNganHan(ten, soTienMucTieu, thoiHanThang);
    mt->datChienLuoc(new ChienLuocNganHan());
    mt->datTrangThai(new TrangThaiChuaXong());
    return mt;
}

MucTieu* MucTieuFactory::taoMucTieuDaiHan(const QString& ten, double soTienMucTieu, int soKyTraGop) {
    MucTieu* mt = new MucTieuDaiHan(ten, soTienMucTieu, soKyTraGop);
    double soTienMoiKy = static_cast<MucTieuDaiHan*>(mt)->getSoTienMoiKy();
    mt->datChienLuoc(new ChienLuocDaiHan(soTienMoiKy));   // Strategy vẫn cần số tiền/kỳ, lấy từ MucTieu vừa tạo
    mt->datTrangThai(new TrangThaiChuaXong());
    return mt;
}
