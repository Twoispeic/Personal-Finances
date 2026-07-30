#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QWidget>
#include "models/NguoiDung.h"

namespace Ui { class DashboardWidget; }

class DashboardWidget : public QWidget {
    Q_OBJECT

public:
    explicit DashboardWidget(QWidget* parent = nullptr);
    ~DashboardWidget();

    void capNhatTongQuan(NguoiDung* nd);

private:
    Ui::DashboardWidget* ui;
};

#endif // DASHBOARDWIDGET_H