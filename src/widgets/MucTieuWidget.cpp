#include "MucTieuWidget.h"
#include "GopTietKiemDialog.h"

MucTieuWidget::MucTieuWidget(MucTieu* mucTieu, QWidget *parent) 
    : QWidget(parent), mucTieuHienTai(mucTieu) {
    
    // Khởi tạo UI
    labelTen = new QLabel("Tên Mục Tiêu", this); // Sẽ lấy từ mucTieu sau
    thanhTienDo = new QProgressBar(this);
    btnGopTien = new QPushButton("Góp Thêm", this);

    // Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(labelTen);
    layout->addWidget(thanhTienDo);
    layout->addWidget(btnGopTien);

    // Khởi tạo hiển thị ban đầu
    hienThiMucTieu();

    // Kết nối Signal & Slot
    connect(btnGopTien, &QPushButton::clicked, this, &MucTieuWidget::onGopNganHanClicked);
}

void MucTieuWidget::hienThiMucTieu() {
    if (!mucTieuHienTai) return;

    // Cập nhật phần trăm từ class MucTieu
    double phanTram = mucTieuHienTai->tinhTienDoPhanTram();
    thanhTienDo->setValue(static_cast<int>(phanTram));

    // Đổi màu Progress Bar dựa trên State Pattern
    capNhatMauSacState();
}

void MucTieuWidget::capNhatMauSacState() {
    /* 
       Chú ý: Vì chưa có file TrangThaiMucTieu.cpp, 
       tui comment đoạn này lại. 
       Khi nhóm bạn code xong State, bạn mở ra là chạy mượt!
    */
    
    // QString mauSac = mucTieuHienTai->layMauSacHienTai(); 
    // QString styleSheet = QString("QProgressBar::chunk { background-color: %1; }").arg(mauSac);
    // thanhTienDo->setStyleSheet(styleSheet);
}

void MucTieuWidget::onGopNganHanClicked() {
    if (!mucTieuHienTai) return;

    // Mở hộp thoại nhập tiền
    GopTietKiemDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        double tienGop = dialog.laySoTienGop();
        
        // Cập nhật vào logic Model
        mucTieuHienTai->capNhatTietKiem(tienGop);
        
        // Cập nhật lại UI
        hienThiMucTieu();
    }
}