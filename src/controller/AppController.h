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


public:
    QString tenNguoiDung() const { return nguoiDungHienTai.getTen(); }
    explicit AppController(QObject* parent = nullptr);

    double tongThuNhap() const;
    double tongChiTieu() const;
    double soDuThang() const;

    ChiTieuController* chiTieu() const { return m_chiTieu; }
    ThuNhapController* thuNhap() const { return m_thuNhap; }
    MucTieuController* mucTieu() const { return m_mucTieu; }

    Q_INVOKABLE double ketThucThang();

signals:
    void duLieuThayDoi();

private:
    NguoiDung nguoiDungHienTai;
    ChiTieuController* m_chiTieu;
    ThuNhapController* m_thuNhap;
    MucTieuController* m_mucTieu;
};

#endif // APPCONTROLLER_H