#ifndef MUCTIEUTAICHINHWIDGET_H
#define MUCTIEUTAICHINHWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "models/NguoiDung.h"

namespace Ui { class MucTieuTaiChinhWidget; }
class MucTieu;

class MucTieuTaiChinhWidget : public QWidget {
    Q_OBJECT
public:
    explicit MucTieuTaiChinhWidget(QWidget* parent = nullptr);
    ~MucTieuTaiChinhWidget();

    void taiLaiDanhSach(NguoiDung* nd);

signals:
    void duLieuThayDoi();
    void yeuCauGopTietKiem(MucTieu* mt);

private slots:
    void onThemMucTieuClicked();

private:
    NguoiDung* nguoiDungHienTai;
    void capNhatOTong(NguoiDung* nd);

    QVBoxLayout* layoutNganHan;
    QVBoxLayout* layoutDaiHan;

    Ui::MucTieuTaiChinhWidget* ui;
};

#endif // MUCTIEUTAICHINHWIDGET_H