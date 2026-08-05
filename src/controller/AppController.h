#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include "models/NguoiDung.h"
#include "controller/ChiTieuController.h"
#include "controller/ThuNhapController.h"
#include "controller/MucTieuController.h"


class AppController : public QObject {
    Q_OBJECT
    Q_PROPERTY(double tongThuNhap READ tongThuNhap NOTIFY duLieuThayDoi)
    Q_PROPERTY(double tongChiTieu READ tongChiTieu NOTIFY duLieuThayDoi)
    Q_PROPERTY(double soDuThang READ soDuThang NOTIFY duLieuThayDoi)
    Q_PROPERTY(ChiTieuController* chiTieu READ chiTieu CONSTANT)
    Q_PROPERTY(ThuNhapController* thuNhap READ thuNhap CONSTANT)
    Q_PROPERTY(MucTieuController* mucTieu READ mucTieu CONSTANT)
    Q_PROPERTY(QString tenNguoiDung READ tenNguoiDung NOTIFY duLieuThayDoi)
    Q_PROPERTY(double huTietKiem READ huTietKiem NOTIFY duLieuThayDoi)


public:
    QString tenNguoiDung() const { return nguoiDungHienTai.getTen(); }
    explicit AppController(QObject* parent = nullptr);

    double tongThuNhap() const;
    double tongChiTieu() const;
    double soDuThang() const;
    double huTietKiem() const;

    ChiTieuController* chiTieu() const { return m_chiTieu; }
    ThuNhapController* thuNhap() const { return m_thuNhap; }
    MucTieuController* mucTieu() const { return m_mucTieu; }

    Q_INVOKABLE double ketThucThang();
    Q_INVOKABLE void lamMoiMucTieu();   // refresh thuần, không chuyển tiền
    Q_INVOKABLE void hoanThanhMucTieu(int id);   // xác nhận hoàn thành + xoá, KHÔNG trả tiền về hũ
    Q_INVOKABLE void quaThangMoi();
    Q_INVOKABLE void refreshDuLieu();

signals:
    void duLieuThayDoi();
    void huTietKiemChanged();

private:
    NguoiDung nguoiDungHienTai;
    ChiTieuController* m_chiTieu;
    ThuNhapController* m_thuNhap;
    MucTieuController* m_mucTieu;
    void dongBoNguoiDungTuDatabase();

    // Logic trả góp mục tiêu dài hạn — DÙNG CHUNG cho cả nút "Refresh" (lamMoiMucTieu)
    // và "Chốt sổ tháng" (ketThucThang), để 2 nơi này không bao giờ trả trùng 1 tháng.
    // Trả tối đa 1 lần/tháng/mục tiêu (idempotent — bấm bao nhiêu lần cũng an toàn) và tự
    // xoá các mục tiêu bị fail-safe (hũ tiền hụt bất thường so với mốc an toàn đã ghi nhận).
    void traGopMucTieuDaiHanThangNay();
};

#endif // APPCONTROLLER_H