#ifndef MUCTIEUCONTROLLER_H
#define MUCTIEUCONTROLLER_H

#include <QObject>
#include <QVariantList>
#include "models/NguoiDung.h"

class MucTieuController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList danhSach READ danhSach NOTIFY duLieuThayDoi)
    Q_PROPERTY(QVariantList danhSachNganHan READ danhSachNganHan NOTIFY duLieuThayDoi)
    Q_PROPERTY(QVariantList danhSachDaiHan READ danhSachDaiHan NOTIFY duLieuThayDoi)
    Q_PROPERTY(int soLuongHoanThanh READ soLuongHoanThanh NOTIFY duLieuThayDoi)
    Q_PROPERTY(double tongDaTietKiem READ tongDaTietKiem NOTIFY duLieuThayDoi)
    Q_PROPERTY(double tongMucTieu READ tongMucTieu NOTIFY duLieuThayDoi)

public:
    explicit MucTieuController(NguoiDung* nd, QObject* parent = nullptr);

    QVariantList danhSach() const;
    QVariantList danhSachNganHan() const;
    QVariantList danhSachDaiHan() const;
    int soLuongHoanThanh() const;
    double tongDaTietKiem() const;
    double tongMucTieu() const;

    Q_INVOKABLE void themNganHan(const QString& ten, double soTien, int thoiHan);
    Q_INVOKABLE void themDaiHan(const QString& ten, double soTien, int soKy);
    Q_INVOKABLE void gop(int mucTieuId, double soTien);
    Q_INVOKABLE void xoa(int id);

    void taiLai();

signals:
    void duLieuThayDoi();
    // Phát ra ngay sau khi góp tiền ngắn hạn thành công, mang theo số tiền THỰC SỰ đã dùng
    // (có thể nhỏ hơn số người dùng nhập, nếu mục tiêu gần đầy) — để AppController trừ
    // đúng số này khỏi hũ tiết kiệm (SoDuLuyKe).
    void daGopTuHuTietKiem(double soTien);

    // Phát ra khi XÓA (hủy) một mục tiêu còn đang dang dở — khác với "Hoàn thành".
    // Xóa nghĩa là huỷ giữa chừng, nên số tiền đã góp vào mục tiêu đó phải HOÀN LẠI vào hũ
    // tiết kiệm (không mất tiền oan), ngược chiều với daGopTuHuTietKiem ở trên.
    void hoanTienVeHu(double soTien);

private:
    NguoiDung* nguoiDung;
    QVariantList m_danhSach;
    QVariantList m_danhSachNganHan;
    QVariantList m_danhSachDaiHan;
    int m_soLuongHoanThanh = 0;
};

#endif // MUCTIEUCONTROLLER_H