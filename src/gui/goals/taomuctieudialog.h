#ifndef TAOMUCTIEUDIALOG_H
#define TAOMUCTIEUDIALOG_H

#include <QDialog>

namespace Ui { class TaoMucTieuDialog; }

class TaoMucTieuDialog : public QDialog {
    Q_OBJECT
public:
    explicit TaoMucTieuDialog(QWidget* parent = nullptr);
    ~TaoMucTieuDialog();

    bool laNganHan() const;
    QString layTen() const;
    double laySoTienMucTieu() const;

    int layThoiHanThang() const;      // chỉ dùng nếu ngắn hạn

    int laySoKyTraGop() const;        // chỉ dùng nếu dài hạn

private:
    bool dangONganHan;

    Ui::TaoMucTieuDialog* ui;
};

#endif // TAOMUCTIEUDIALOG_H