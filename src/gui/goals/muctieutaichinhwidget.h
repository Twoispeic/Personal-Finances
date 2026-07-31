#ifndef MUCTIEUTAICHINHWIDGET_H
#define MUCTIEUTAICHINHWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "models/NguoiDung.h"

namespace Ui { class muctieutaichinhwidget; }
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
    void capNhatOTong(NguoiDung* nd);

    QVBoxLayout* layoutNganHan;
    QVBoxLayout* layoutDaiHan;

    Ui::muctieutaichinhwidget* ui;
};

#endif // MUCTIEUTAICHINHWIDGET_H