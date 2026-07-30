#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "models/NguoiDung.h"

namespace Ui { class MainWindow; }
class DashboardWidget;
class ThuNhapChiTieuWidget;
class MucTieuWidget;
class BieuDoWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void capNhatGiaoDien();

private slots:
    void onKetThucThangClicked();
    void onMoDialogGopTietKiem(MucTieu* mt);

private:
    NguoiDung nguoiDungHienTai;
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H