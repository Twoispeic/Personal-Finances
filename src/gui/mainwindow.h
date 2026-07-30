#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "models/NguoiDung.h"

namespace Ui { class MainWindow; }
class SidebarWidget;
class TrangChuWidget;
class QuanLyChiTieuWidget;
class ThuNhapCaNhanWidget;
class MucTieuTaiChinhWidget;
class MucTieu;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void capNhatTatCaTrang();

private slots:
    void onSidebarChonTrang(int chiSoTrang);
    void onMoDialogGopTietKiem(MucTieu* mt);

private:
    NguoiDung nguoiDungHienTai;

    SidebarWidget* sidebar;
    TrangChuWidget* trangChu;
    QuanLyChiTieuWidget* quanLyChiTieu;
    ThuNhapCaNhanWidget* thuNhapCaNhan;
    MucTieuTaiChinhWidget* mucTieuTaiChinh;

    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H