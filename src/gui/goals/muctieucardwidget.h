#ifndef MUCTIEUCARDWIDGET_H
#define MUCTIEUCARDWIDGET_H

#include <QWidget>
#include "goals/MucTieu.h"

namespace Ui { class muctieucardwidget; }

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
    Ui::muctieucardwidget* ui;
};

#endif // MUCTIEUCARDWIDGET_H