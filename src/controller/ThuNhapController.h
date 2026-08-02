#ifndef THUNHAPCONTROLLER_H
#define THUNHAPCONTROLLER_H

#include <QObject>
#include "models/NguoiDung.h"

class ThuNhapController : public QObject {
    Q_OBJECT
public:
    explicit ThuNhapController(NguoiDung* nd, QObject* parent = nullptr);

    Q_INVOKABLE void luuThang(double soTien);

signals:
    void duLieuThayDoi();

private:
    NguoiDung* nguoiDung;
};

#endif // THUNHAPCONTROLLER_H