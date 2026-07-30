#include "MucTieuWidget.h"
#include <QDebug> // Dùng để in log kiểm tra lúc chạy

// Hàm khởi tạo (Constructor)
MucTieuWidget::MucTieuWidget(MucTieu* mucTieu, QWidget *parent)
    : QWidget(parent), mucTieuHienTai(mucTieu)
{
    // 1. Khởi tạo các thành phần giao diện (UI Components)
    labelTen = new QLabel("Tên mục tiêu: Đang tải...", this);
    thanhTienDo = new QProgressBar(this);
    btnGopTien = new QPushButton("Góp Tiền", this);
    
    // Cài đặt thông số cơ bản cho thanh tiến độ
    thanhTienDo->setMinimum(0);
    thanhTienDo->setMaximum(100);
    thanhTienDo->setValue(0);
    
    // 2. Sắp xếp bố cục (Layout) theo chiều dọc
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(labelTen);
    layout->addWidget(thanhTienDo);
    layout->addWidget(btnGopTien);
    
    setLayout(layout); // Áp dụng bố cục cho Widget này
    
    // 3. Kết nối nút bấm với sự kiện
    connect(btnGopTien, &QPushButton::clicked, this, &MucTieuWidget::onGopNganHanClicked);
    
    // 4. Nếu đã có dữ liệu mục tiêu truyền vào thì cập nhật lên giao diện
    if (mucTieuHienTai != nullptr) {
        hienThiMucTieu();
        capNhatMauSacState();
    }
}

// Hàm cập nhật giao diện dựa trên dữ liệu thật
void MucTieuWidget::hienThiMucTieu()
{
    if (!mucTieuHienTai) return;
    
    /* 
     * LƯU Ý: Chỗ này tui giả định class MucTieu của bạn có 2 hàm getTen() và getTienDo().
     * Nếu bạn đặt tên hàm khác trong MucTieu.h (vd: layTen(), phanTram()...) thì nhớ sửa lại ở 2 dòng dưới nha! 
     */
    // labelTen->setText("Tên mục tiêu: " + mucTieuHienTai->getTen());
    // thanhTienDo->setValue(mucTieuHienTai->getTienDo());
}

// Hàm đổi màu thanh tiến độ dựa trên State Pattern
void MucTieuWidget::capNhatMauSacState()
{
    // Tui để sẵn sườn code đổi màu ở đây. 
    // Sau này logic State trả về trạng thái gì thì bạn đổi màu đó nha.
    
    // Ví dụ đổi màu thanh tiến độ sang xanh lá:
    // QString styleSheet = "QProgressBar::chunk { background-color: #4CAF50; }";
    // thanhTienDo->setStyleSheet(styleSheet);
}

// Hàm xử lý sự kiện khi bấm nút "Góp Tiền"
void MucTieuWidget::onGopNganHanClicked()
{
    qDebug() << "Nút Góp Tiền đã được bấm!";
    
    // Logic dự kiến ở đây:
    // Mở cái cửa sổ GopTietKiemDialog lên để người dùng nhập số tiền
    // GopTietKiemDialog dialog(this);
    // dialog.exec();
}