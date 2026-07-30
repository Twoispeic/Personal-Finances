#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QPushButton>

#include "models/NguoiDung.h"
#include "database/ChiTieuRepository.h"
#include "database/NguoiDungRepository.h"

#include "dashboardwidget.h"
#include "thunhapchitieuwidget.h"
#include "muctieuwidget.h"
#include "bieudowidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/*
 * MainWindow - ghep 4 widget: Dashboard, ThuNhapChiTieu, MucTieu, BieuDo.
 *
 * Luong hoat dong:
 *   1. ThuNhapChiTieuWidget luu du lieu -> phat duLieuDaThayDoi()
 *   2. MainWindow lang nghe -> goi capNhatGiaoDien()
 *   3. capNhatGiaoDien() day du lieu moi xuong Dashboard + BieuDo (+ MucTieu)
 *
 * onKetThucThangClicked() goi thang nguoiDungHienTai.ketThucThang() co san
 * trong NguoiDung (da gom san phanBoTienTietKiem() + xoa buffer RAM thang cu).
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

public slots:
    void onKetThucThangClicked();
    void capNhatGiaoDien();

private:
    Ui::MainWindow* ui;

    NguoiDung nguoiDungHienTai;
    ChiTieuRepository repoChiTieu; // dung rieng de lay Map cho BieuDoWidget

    QTabWidget* tabChinh;
    DashboardWidget* dashboard;
    ThuNhapChiTieuWidget* formThuChi;
    MucTieuWidget* widgetMucTieu;
    BieuDoWidget* widgetBieuDo;
    QPushButton* nutKetThucThang;

    void khoiTaoKetNoiDatabase();
    void khoiTaoGiaoDien();
    void ketNoiTinHieu();
};

#endif // MAINWINDOW_H
