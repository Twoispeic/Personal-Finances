#ifndef MUCTIEUCARDWIDGET_H
#define MUCTIEUCARDWIDGET_H

#include <QWidget>
#include "goals/MucTieu.h"

namespace Ui { class MucTieuCardWidget; }

class MucTieuCardWidget : public QWidget {
    Q_OBJECT
public:
    explicit MucTieuCardWidget(MucTieu* mt, QWidget* parent = nullptr);
    ~MucTieuCardWidget();

signals:
    void yeuCauGopTietKiem(MucTieu* mt);

private slots:
    void onGopClicked();

private:
    MucTieu* mucTieuGanVoi;
    Ui::MucTieuCardWidget* ui;
};

#endif // MUCTIEUCARDWIDGET_H