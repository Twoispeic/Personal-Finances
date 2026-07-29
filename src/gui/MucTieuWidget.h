#ifndef MUCTIEUWIDGET_H
#define MUCTIEUWIDGET_H

#include <QWidget>
#include "goals/MucTieu.h"

namespace Ui { class MucTieuWidget; }

class MucTieuWidget : public QWidget {
    Q_OBJECT

public:
    explicit MucTieuWidget(QWidget* parent = nullptr);
    ~MucTieuWidget();

    void hienThiMucTieu(MucTieu* mt);

signals:
    void yeuCauGopTietKiem(MucTieu* mt);   // MainWindow lắng nghe, mở GopTietKiemDialog

private slots:
    void onGopNganHanClicked();

private:
    MucTieu* mucTieuHienTai;
    Ui::MucTieuWidget* ui;
};

#endif // MUCTIEUWIDGET_H