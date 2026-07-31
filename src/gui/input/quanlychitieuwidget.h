#ifndef QUANLYCHITIEUWIDGET_H
#define QUANLYCHITIEUWIDGET_H

#include <QWidget>

namespace Ui { class quanlychitieuwidget; }

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
    Ui::quanlychitieuwidget* ui;
};

#endif // QUANLYCHITIEUWIDGET_H