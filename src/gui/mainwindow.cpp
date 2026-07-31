#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sidebarwidget.h"
#include "input/trangchuwidget.h"
#include "input/quanlychitieuwidget.h"
#include "input/thunhapcanhanwidget.h"
#include "goals/muctieutaichinhwidget.h"
#include "goals/goptietkiemdialog.h"

#include "database/NguoiDungRepository.h"

#include <QHBoxLayout>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , nguoiDungHienTai("", "")
{
    ui->setupUi(this);

    // Nạp lại thông tin người dùng đã lưu trước đó (nếu có)
    NguoiDungRepository ndRepo;
    ndRepo.taoBang();
    NguoiDung daLuu = ndRepo.layThongTinNguoiDung();
    nguoiDungHienTai.setTen(daLuu.getTen());
    nguoiDungHienTai.setCongViec(daLuu.getCongViec());

    // Tạo sidebar + 4 trang
    sidebar = new SidebarWidget(this);
    trangChu = new TrangChuWidget(this);
    quanLyChiTieu = new QuanLyChiTieuWidget(this);
    thuNhapCaNhan = new ThuNhapCaNhanWidget(this);
    mucTieuTaiChinh = new MucTieuTaiChinhWidget(this);

    QStackedWidget* stackedPages = new QStackedWidget(this);
    stackedPages->addWidget(trangChu);         // index 0
    stackedPages->addWidget(quanLyChiTieu);    // index 1
    stackedPages->addWidget(thuNhapCaNhan);    // index 2
    stackedPages->addWidget(mucTieuTaiChinh);  // index 3
    stackedPages->setCurrentIndex(0);

    QWidget* khungTrungTam = new QWidget(this);
    QHBoxLayout* layoutChinh = new QHBoxLayout(khungTrungTam);
    layoutChinh->setContentsMargins(0, 0, 0, 0);
    layoutChinh->setSpacing(0);
    layoutChinh->addWidget(sidebar);
    layoutChinh->addWidget(stackedPages, 1);   // stretch = 1, chiếm hết phần còn lại
    setCentralWidget(khungTrungTam);

    // Nối tín hiệu chuyển trang
    connect(sidebar, &SidebarWidget::trangDuocChon, this, [stackedPages](int chiSo) {
        stackedPages->setCurrentIndex(chiSo);
    });

    // Nối tín hiệu dữ liệu thay đổi -> cập nhật lại toàn bộ trang
    connect(trangChu, &TrangChuWidget::duLieuThayDoi, this, &MainWindow::capNhatTatCaTrang);
    connect(quanLyChiTieu, &QuanLyChiTieuWidget::duLieuThayDoi, this, &MainWindow::capNhatTatCaTrang);
    connect(thuNhapCaNhan, &ThuNhapCaNhanWidget::duLieuThayDoi, this, &MainWindow::capNhatTatCaTrang);
    connect(mucTieuTaiChinh, &MucTieuTaiChinhWidget::duLieuThayDoi, this, &MainWindow::capNhatTatCaTrang);
    connect(mucTieuTaiChinh, &MucTieuTaiChinhWidget::yeuCauGopTietKiem, this, &MainWindow::onMoDialogGopTietKiem);

    capNhatTatCaTrang();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::capNhatTatCaTrang() {
    trangChu->capNhatTongQuan(&nguoiDungHienTai);
    quanLyChiTieu->taiLaiDanhSach();
    thuNhapCaNhan->hienThiSoTienThangHienTai(nguoiDungHienTai.tinhTongThuNhap());
    mucTieuTaiChinh->taiLaiDanhSach(&nguoiDungHienTai);
}

void MainWindow::onSidebarChonTrang(int chiSoTrang) {
    // Không dùng tới vì đã nối trực tiếp qua lambda ở constructor,
    // giữ lại khai báo để khớp .h, có thể xoá slot này nếu không cần
}

void MainWindow::onMoDialogGopTietKiem(MucTieu* mt) {
    double conDu = nguoiDungHienTai.tinhSoDuThang();
    GopTietKiemDialog dlg(conDu, mt, this);
    if (dlg.exec() == QDialog::Accepted) {
        nguoiDungHienTai.gopTietKiemNganHan(mt, dlg.laySoTienGop());
        capNhatTatCaTrang();
    }
}