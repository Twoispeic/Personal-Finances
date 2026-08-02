#ifndef MUCTIEUCONTROLLER_H
#define MUCTIEUCONTROLLER_H

#include <QObject>
#include <QVariantList>
#include "models/NguoiDung.h"

class MucTieuController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList danhSach READ danhSach NOTIFY duLieuThayDoi)

public:
    explicit MucTieuController(NguoiDung* nd, QObject* parent = nullptr);

    QVariantList danhSach() const;

    Q_INVOKABLE void themNganHan(const QString& ten, double soTien, int thoiHan);
    Q_INVOKABLE void themDaiHan(const QString& ten, double soTien, int soKy);
    Q_INVOKABLE void gop(int mucTieuId, double soTien);

    void taiLai();

signals:
    void duLieuThayDoi();

private:
    NguoiDung* nguoiDung;
    QVariantList m_danhSach;
};

#endif // MUCTIEUCONTROLLER_H