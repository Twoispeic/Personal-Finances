#ifndef MUCTIEUCONTROLLER_H
#define MUCTIEUCONTROLLER_H

#include <QObject>
#include <QVariantList>
#include "models/NguoiDung.h"

class MucTieuController : public QObject {
    Q_OBJECT
    // Danh sách chung
    Q_PROPERTY(QVariantList danhSach READ danhSach NOTIFY duLieuThayDoi)

    // BỔ SUNG: Tách riêng danh sách cho Trang Chủ & Trang Mục Tiêu dễ render UI khác nhau
    Q_PROPERTY(QVariantList danhSachNganHan READ danhSachNganHan NOTIFY duLieuThayDoi)
    Q_PROPERTY(QVariantList danhSachDaiHan READ danhSachDaiHan NOTIFY duLieuThayDoi)

    // BỔ SUNG: Đếm số lượng mục tiêu đã hoàn thành (dùng cho khu vực tổng quan)
    Q_PROPERTY(int soLuongHoanThanh READ soLuongHoanThanh NOTIFY duLieuThayDoi)

public:
    explicit MucTieuController(NguoiDung* nd, QObject* parent = nullptr);

    QVariantList danhSach() const;
    QVariantList danhSachNganHan() const;
    QVariantList danhSachDaiHan() const;
    int soLuongHoanThanh() const;

    Q_INVOKABLE void themNganHan(const QString& ten, double soTien, int thoiHan);
    Q_INVOKABLE void themDaiHan(const QString& ten, double soTien, int soKy);
    Q_INVOKABLE void gop(int mucTieuId, double soTien);

    void taiLai();

signals:
    void duLieuThayDoi();

private:
    NguoiDung* nguoiDung;
    QVariantList m_danhSach;
    QVariantList m_danhSachNganHan;
    QVariantList m_danhSachDaiHan;
    int m_soLuongHoanThanh = 0;
};

#endif // MUCTIEUCONTROLLER_H