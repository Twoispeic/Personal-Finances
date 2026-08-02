#ifndef CHITIEUCONTROLLER_H
#define CHITIEUCONTROLLER_H

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include "models/NguoiDung.h"

class ChiTieuController : public QObject {
    Q_OBJECT
    // Danh sách toàn bộ để dùng cho lịch sử/bộ lọc
    Q_PROPERTY(QVariantList danhSach READ danhSach NOTIFY duLieuThayDoi)

    // Dữ liệu đã được tính % cho Biểu đồ tròn
    Q_PROPERTY(QVariantList thongKeBieuDo READ thongKeBieuDo NOTIFY duLieuThayDoi)

    // BỔ SUNG: Danh sách lọc riêng "Các khoản chưa xác định" (Loại KHAC)
    Q_PROPERTY(QVariantList danhSachChuaXacDinh READ danhSachChuaXacDinh NOTIFY duLieuThayDoi)

public:
    explicit ChiTieuController(NguoiDung* nd, QObject* parent = nullptr);

    QVariantList danhSach() const;
    QVariantList thongKeBieuDo() const;
    QVariantList danhSachChuaXacDinh() const;

    Q_INVOKABLE void them(int loai, double soTien);
    Q_INVOKABLE void locTheoLoai(int loai);
    Q_INVOKABLE void locTatCa();

signals:
    void duLieuThayDoi();

private:
    void taiLai();
    NguoiDung* nguoiDung;
    QVariantList m_danhSach;
    QVariantList m_thongKeBieuDo;
    QVariantList m_danhSachChuaXacDinh;
};

#endif// CHITIEUCONTROLLER_H