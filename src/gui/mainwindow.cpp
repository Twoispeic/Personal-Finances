#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database/KetNoiDatabase.h"
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), nguoiDungHienTai("Thuận", "Sinh viên") {
    ui->setupUi(this);

    khoiTaoKetNoiDatabase();
    khoiTaoGiaoDien();
    ketNoiTinHieu();
    capNhatGiaoDien();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::khoiTaoKetNoiDatabase() {
    // Mo ket noi + tao bang cho toan bo repository, mot lan duy nhat luc khoi dong.
    // (KetNoiDatabase la Singleton nen goi moKetNoi() nhieu lan tu cac repo khac
    //  van an toan, khong tao ket noi trung.)
    KetNoiDatabase::getInstance().moKetNoi();
    repoChiTieu.taoBang();
}

void MainWindow::khoiTaoGiaoDien() {
    setWindowTitle("Quản lý Tài chính Cá nhân");

    QVBoxLayout* layoutTrungTam = new QVBoxLayout(ui->centralwidget);

    nutKetThucThang = new QPushButton("Kết thúc tháng", ui->centralwidget);
    layoutTrungTam->addWidget(nutKetThucThang, 0, Qt::AlignRight);

    tabChinh = new QTabWidget(ui->centralwidget);

    dashboard = new DashboardWidget(tabChinh);
    formThuChi = new ThuNhapChiTieuWidget(tabChinh);
    widgetMucTieu = new MucTieuWidget(tabChinh);
    widgetBieuDo = new BieuDoWidget(tabChinh);

    tabChinh->addTab(dashboard, "Tổng quan");
    tabChinh->addTab(formThuChi, "Thu / Chi");
    tabChinh->addTab(widgetMucTieu, "Mục tiêu");
    tabChinh->addTab(widgetBieuDo, "Biểu đồ");

    layoutTrungTam->addWidget(tabChinh);
    ui->centralwidget->setLayout(layoutTrungTam);

    resize(900, 650);
}

void MainWindow::ketNoiTinHieu() {
    connect(formThuChi, &ThuNhapChiTieuWidget::duLieuDaThayDoi,
            this, &MainWindow::capNhatGiaoDien);
    connect(nutKetThucThang, &QPushButton::clicked,
            this, &MainWindow::onKetThucThangClicked);

    formThuChi->setNguoiDung(&nguoiDungHienTai);
}

void MainWindow::onKetThucThangClicked() {
    double soDuTruocKhiChia = nguoiDungHienTai.tinhSoDuThang();

    if (soDuTruocKhiChia <= 0) {
        QMessageBox::information(this, "Kết thúc tháng",
            "Không có số dư dương để chia vào mục tiêu tiết kiệm tháng này.");
        return;
    }

    // ketThucThang() da tu goi phanBoTienTietKiem() roi xoa buffer RAM thang cu
    nguoiDungHienTai.ketThucThang();

    capNhatGiaoDien();

    QMessageBox::information(this, "Kết thúc tháng",
        QString("Đã kết thúc tháng. Số dư %1 đ đã được xử lý phân bổ vào các mục tiêu dài hạn (nếu có).\n"
                "Dữ liệu thu/chi trong RAM đã được làm mới cho tháng tiếp theo.")
            .arg(soDuTruocKhiChia, 0, 'f', 0));
}

void MainWindow::capNhatGiaoDien() {
    dashboard->capNhatTongQuan(&nguoiDungHienTai);
    widgetBieuDo->veBieuDoChiTieu(repoChiTieu.tinhTongTheoLoai());

    // Placeholder MucTieuWidget hien 1 muc tieu; khi co file that cua nguoi
    // phu trach, ho co the tu lay danh sach qua MucTieuRepository roi lap
    // goi hienThiMucTieu(mt) cho tung cai, khong can sua MainWindow.
}
