#include "AppController.h"
#include "database/NguoiDungRepository.h"

AppController::AppController(QObject* parent)
    : QObject(parent), nguoiDungHienTai("", "")
{
    NguoiDungRepository ndRepo;
    ndRepo.taoBang();
    NguoiDung daLuu = ndRepo.layThongTinNguoiDung();
    nguoiDungHienTai.setTen(daLuu.getTen());
    nguoiDungHienTai.setCongViec(daLuu.getCongViec());

    m_chiTieu = new ChiTieuController(&nguoiDungHienTai, this);
    m_thuNhap = new ThuNhapController(&nguoiDungHienTai, this);
    m_mucTieu = new MucTieuController(&nguoiDungHienTai, this);

    // Khi 1 trong 3 controller con đổi dữ liệu -> AppController cũng báo thay đổi (vì tongThuNhap/tongChiTieu phụ thuộc chúng)
    connect(m_chiTieu, &ChiTieuController::duLieuThayDoi, this, &AppController::duLieuThayDoi);
    connect(m_thuNhap, &ThuNhapController::duLieuThayDoi, this, &AppController::duLieuThayDoi);
    connect(m_mucTieu, &MucTieuController::duLieuThayDoi, this, &AppController::duLieuThayDoi);
}

double AppController::tongThuNhap() const { return nguoiDungHienTai.tinhTongThuNhap(); }
double AppController::tongChiTieu() const { return nguoiDungHienTai.tinhTongChiTieu(); }
double AppController::soDuThang() const { return nguoiDungHienTai.tinhSoDuThang(); }

double AppController::ketThucThang() {
    double conDu = nguoiDungHienTai.phanBoTienTietKiem();
    m_mucTieu->taiLai();
    emit duLieuThayDoi();
    return conDu;
}