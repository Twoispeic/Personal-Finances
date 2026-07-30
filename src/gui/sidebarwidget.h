#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QWidget>

namespace Ui { class SidebarWidget; }

class SidebarWidget : public QWidget {
    Q_OBJECT
public:
    explicit SidebarWidget(QWidget* parent = nullptr);
    ~SidebarWidget();

signals:
    void trangDuocChon(int chiSoTrang);   // 0=TrangChu, 1=QuanLyChiTieu, 2=ThuNhapCaNhan, 3=MucTieuTaiChinh

private slots:
    void onNutTrangChuClicked();
    void onNutChiTieuClicked();
    void onNutThuNhapClicked();
    void onNutMucTieuClicked();

private:
    Ui::SidebarWidget* ui;
};

#endif // SIDEBARWIDGET_H