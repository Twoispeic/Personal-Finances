#ifndef BIEUDOWIDGET_H
#define BIEUDOWIDGET_H

#include <QWidget>
#include <QMap>
#include "models/ChiTieu.h"

namespace Ui { class BieuDoWidget; }

class BieuDoWidget : public QWidget {
    Q_OBJECT
public:
    explicit BieuDoWidget(QWidget* parent = nullptr);
    ~BieuDoWidget();

    void veBieuDoChiTieu(const QMap<LoaiChiTieu, double>& duLieu);

private:
    Ui::BieuDoWidget* ui;
};

#endif // BIEUDOWIDGET_H