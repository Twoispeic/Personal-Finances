#ifndef THUNHAPCANHANWIDGET_H
#define THUNHAPCANHANWIDGET_H

#include <QWidget>

namespace Ui { class thunhapcanhanwidget; }

class ThuNhapCaNhanWidget : public QWidget {
    Q_OBJECT
public:
    explicit ThuNhapCaNhanWidget(QWidget* parent = nullptr);
    ~ThuNhapCaNhanWidget();

    void hienThiSoTienThangHienTai(double soTien);

signals:
    void duLieuThayDoi();

private slots:
    void onLuuThuNhapClicked();

private:
    Ui::thunhapcanhanwidget* ui;
};

#endif // THUNHAPCANHANWIDGET_H