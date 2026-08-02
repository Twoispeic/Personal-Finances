#ifndef CHITIEUCONTROLLER_H
#define CHITIEUCONTROLLER_H

#include <QObject>
#include <QVariantList>
#include "models/NguoiDung.h"

class ChiTieuController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList danhSach READ danhSach NOTIFY duLieuThayDoi)

public:
    explicit ChiTieuController(NguoiDung* nd, QObject* parent = nullptr);

    QVariantList danhSach() const;

    Q_INVOKABLE void them(int loai, double soTien);
    Q_INVOKABLE void locTheoLoai(int loai);
    Q_INVOKABLE void locTatCa();

signals:
    void duLieuThayDoi();

private:
    void taiLai();
    NguoiDung* nguoiDung;
    QVariantList m_danhSach;
};

#endif // CHITIEUCONTROLLER_H