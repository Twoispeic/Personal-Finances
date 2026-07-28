#ifndef CHITIEUREPOSITORY_H
#define CHITIEUREPOSITORY_H

#include <QList>
#include <QMap>
#include "models/ChiTieu.h"

class ChiTieuRepository {
public:
    ChiTieuRepository();
    bool taoBang();
    bool them(const ChiTieu &chiTieu);
    QList<ChiTieu> layTatCa();
    QMap<LoaiChiTieu, double> tinhTongTheoLoai();

private:
    QString loaiSangText(LoaiChiTieu loai) const;
    LoaiChiTieu textSangLoai(const QString &text) const;
};

#endif // CHITIEUREPOSITORY_H