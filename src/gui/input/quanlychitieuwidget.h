#ifndef QUANLYCHITIEUWIDGET_H
#define QUANLYCHITIEUWIDGET_H

#include <QWidget>

namespace Ui { class QuanLyChiTieuWidget; }

class QuanLyChiTieuWidget : public QWidget {
    Q_OBJECT
public:
    explicit QuanLyChiTieuWidget(QWidget* parent = nullptr);
    ~QuanLyChiTieuWidget();

    void taiLaiDanhSach();

signals:
    void duLieuThayDoi();

private slots:
    void onThemChiTieuClicked();
    void onLocThayDoi();

private:
    Ui::QuanLyChiTieuWidget* ui;
};

#endif // QUANLYCHITIEUWIDGET_H