#ifndef TRANGCHUWIDGET_H
#define TRANGCHUWIDGET_H

#include <QWidget>
#include "models/NguoiDung.h"

namespace Ui { class TrangChuWidget; }
class BieuDoWidget;

class TrangChuWidget : public QWidget {
    Q_OBJECT
public:
    explicit TrangChuWidget(QWidget* parent = nullptr);
    ~TrangChuWidget();

    void capNhatTongQuan(NguoiDung* nd);

signals:
    void duLieuThayDoi();

private slots:
    void onKetThucThangClicked();

private:
    BieuDoWidget* bieuDoThuNho;
    Ui::TrangChuWidget* ui;
    NguoiDung* nguoiDungHienTai;
};

#endif // TRANGCHUWIDGET_H