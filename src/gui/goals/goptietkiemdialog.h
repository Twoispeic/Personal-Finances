#ifndef GOPTIETKIEMDIALOG_H
#define GOPTIETKIEMDIALOG_H

#include <QDialog>
#include "goals/MucTieu.h"

namespace Ui { class GopTietKiemDialog; }

class GopTietKiemDialog : public QDialog {
    Q_OBJECT
public:
    explicit GopTietKiemDialog(double soTienConDu, MucTieu* mucTieu, QWidget* parent = nullptr);
    ~GopTietKiemDialog();

    double laySoTienGop() const;

private:
    double soTienConDu;
    MucTieu* mucTieuDuocChon;
    Ui::GopTietKiemDialog* ui;
};

#endif // GOPTIETKIEMDIALOG_H