#ifndef THEMCHITIEUDIALOG_H
#define THEMCHITIEUDIALOG_H

#include <QDialog>
#include "models/ChiTieu.h"

namespace Ui { class ThemChiTieuDialog; }

class ThemChiTieuDialog : public QDialog {
    Q_OBJECT
public:
    explicit ThemChiTieuDialog(QWidget* parent = nullptr);
    ~ThemChiTieuDialog();

    ChiTieu layChiTieuMoi() const;

private:
    Ui::ThemChiTieuDialog* ui;
};

#endif // THEMCHITIEUDIALOG_H