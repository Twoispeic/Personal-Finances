#ifndef MUCTIEUWIDGET_H
#define MUCTIEUWIDGET_H

#include <QWidget>
#include <QProgressBar>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "../goals/MucTieu.h"

class MucTieuWidget : public QWidget {
    Q_OBJECT
private:
    MucTieu* mucTieuHienTai; 
    QProgressBar* thanhTienDo; // Từ UML
    QLabel* labelTen;
    QPushButton* btnGopTien;

public:
    explicit MucTieuWidget(MucTieu* mucTieu, QWidget *parent = nullptr);
    void hienThiMucTieu(); // Cập nhật UI
    void capNhatMauSacState(); // Hàm phụ xử lý State Pattern

private slots:
    void onGopNganHanClicked(); // Xử lý khi bấm nút góp tiền
};

#endif // MUCTIEUWIDGET_H