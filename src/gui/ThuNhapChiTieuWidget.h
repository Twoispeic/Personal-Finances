#ifndef THUNHAPCHITIEUWIDGET_H
#define THUNHAPCHITIEUWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QPushButton>
#include <QTableWidget>

#include "models/NguoiDung.h"
#include "database/ThuNhapRepository.h"
#include "database/ChiTieuRepository.h"

/*
 * ThuNhapChiTieuWidget - form nhap Thu nhap / Chi tieu + bang danh sach co loc.
 *
 * Ghi chu quan trong: NguoiDung KHONG co getter danh sach ChiTieu, nen bang
 * hien thi va bo loc lay du lieu truc tiep tu ChiTieuRepository (SQLite),
 * khong lay tu NguoiDung. NguoiDung chi giu buffer RAM de tinh tong thang.
 */
class ThuNhapChiTieuWidget : public QWidget {
    Q_OBJECT

public:
    explicit ThuNhapChiTieuWidget(QWidget* parent = nullptr);

    // Gan nguoi dung hien tai (do MainWindow quan ly) de widget biet luu vao dau
    void setNguoiDung(NguoiDung* nguoiDungMoi);

public slots:
    void onLuuThuNhapClicked();
    void onLuuChiTieuClicked();
    void onLocThayDoi();

signals:
    // MainWindow lang nghe tin hieu nay de goi capNhatGiaoDien()
    void duLieuDaThayDoi();

private:
    NguoiDung* nguoiDung = nullptr;
    ThuNhapRepository repoThuNhap;
    ChiTieuRepository repoChiTieu;

    // --- Form Thu nhap ---
    QLineEdit* editLoaiThuNhap;
    QDoubleSpinBox* spinSoTienThuNhap;
    QDateEdit* dateThuNhap;
    QPushButton* nutLuuThuNhap;

    // --- Form Chi tieu ---
    QComboBox* comboLoaiChiTieu;
    QDoubleSpinBox* spinSoTienChiTieu;
    QDateEdit* dateChiTieu;
    QPushButton* nutLuuChiTieu;

    // --- Bo loc + bang danh sach ---
    QComboBox* comboLocLoai;
    QDateEdit* dateLocTu;
    QDateEdit* dateLocDen;
    QTableWidget* bangGiaoDich;

    void khoiTaoGiaoDien();
    void ketNoiTinHieu();
    void hienThiDanhSach(const QList<ChiTieu>& danhSach);
    QString tenHienThi(LoaiChiTieu loai) const;
    bool kiemTraHopLeSoTien(double soTien);
};

#endif // THUNHAPCHITIEUWIDGET_H
