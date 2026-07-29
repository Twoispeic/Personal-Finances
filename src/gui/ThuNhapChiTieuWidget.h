#ifndef THUNHAPCHITIEUWIDGET_H
#define THUNHAPCHITIEUWIDGET_H

#include <QWidget>

namespace Ui { class ThuNhapChiTieuWidget; }

class ThuNhapChiTieuWidget : public QWidget {
    Q_OBJECT

public:
    explicit ThuNhapChiTieuWidget(QWidget* parent = nullptr);
    ~ThuNhapChiTieuWidget();

signals:
    void duLieuThayDoi();   // phát ra sau khi lưu thành công, để MainWindow cập nhật Dashboard

private slots:
    void onLuuThuNhapClicked();
    void onLuuChiTieuClicked();
    void onLocThayDoi();

private:
    Ui::ThuNhapChiTieuWidget* ui;
};

#endif // THUNHAPCHITIEUWIDGET_H