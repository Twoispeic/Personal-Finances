#include "thunhapchitieuwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>

ThuNhapChiTieuWidget::ThuNhapChiTieuWidget(QWidget* parent) : QWidget(parent) {
    // Dam bao 2 bang da ton tai truoc khi dung (idempotent, khong sao neu goi lai)
    repoThuNhap.taoBang();
    repoChiTieu.taoBang();

    khoiTaoGiaoDien();
    ketNoiTinHieu();
    onLocThayDoi(); // nap bang lan dau
}

void ThuNhapChiTieuWidget::setNguoiDung(NguoiDung* nguoiDungMoi) {
    nguoiDung = nguoiDungMoi;
}

// ================= GIAO DIEN =================

void ThuNhapChiTieuWidget::khoiTaoGiaoDien() {
    QVBoxLayout* layoutChinh = new QVBoxLayout(this);

    // ---- Form Thu nhap + Chi tieu canh nhau ----
    QHBoxLayout* layoutForm = new QHBoxLayout();

    QGroupBox* khungThuNhap = new QGroupBox("Thêm thu nhập", this);
    QFormLayout* formThuNhap = new QFormLayout();

    editLoaiThuNhap = new QLineEdit(khungThuNhap);
    editLoaiThuNhap->setPlaceholderText("VD: Lương, tiền tiêu vặt...");

    spinSoTienThuNhap = new QDoubleSpinBox(khungThuNhap);
    spinSoTienThuNhap->setRange(0, 1000000000);
    spinSoTienThuNhap->setSuffix(" đ");
    spinSoTienThuNhap->setGroupSeparatorShown(true);

    dateThuNhap = new QDateEdit(QDate::currentDate(), khungThuNhap);
    dateThuNhap->setCalendarPopup(true);

    nutLuuThuNhap = new QPushButton("Lưu thu nhập", khungThuNhap);

    formThuNhap->addRow("Loại:", editLoaiThuNhap);
    formThuNhap->addRow("Số tiền:", spinSoTienThuNhap);
    formThuNhap->addRow("Ngày:", dateThuNhap);
    formThuNhap->addRow(nutLuuThuNhap);
    khungThuNhap->setLayout(formThuNhap);

    QGroupBox* khungChiTieu = new QGroupBox("Thêm chi tiêu", this);
    QFormLayout* formChiTieu = new QFormLayout();

    comboLoaiChiTieu = new QComboBox(khungChiTieu);
    comboLoaiChiTieu->addItem("Điện nước - Wifi", int(DIEN_NUOC_WIFI));
    comboLoaiChiTieu->addItem("Trọ - Ăn uống", int(TRO_AN_UONG));
    comboLoaiChiTieu->addItem("Khác", int(KHAC));

    spinSoTienChiTieu = new QDoubleSpinBox(khungChiTieu);
    spinSoTienChiTieu->setRange(0, 1000000000);
    spinSoTienChiTieu->setSuffix(" đ");
    spinSoTienChiTieu->setGroupSeparatorShown(true);

    dateChiTieu = new QDateEdit(QDate::currentDate(), khungChiTieu);
    dateChiTieu->setCalendarPopup(true);

    nutLuuChiTieu = new QPushButton("Lưu chi tiêu", khungChiTieu);

    formChiTieu->addRow("Danh mục:", comboLoaiChiTieu);
    formChiTieu->addRow("Số tiền:", spinSoTienChiTieu);
    formChiTieu->addRow("Ngày:", dateChiTieu);
    formChiTieu->addRow(nutLuuChiTieu);
    khungChiTieu->setLayout(formChiTieu);

    layoutForm->addWidget(khungThuNhap);
    layoutForm->addWidget(khungChiTieu);

    // ---- Bo loc ----
    QGroupBox* khungLoc = new QGroupBox("Bộ lọc danh sách chi tiêu", this);
    QHBoxLayout* layoutLoc = new QHBoxLayout();

    comboLocLoai = new QComboBox(khungLoc);
    comboLocLoai->addItem("Tất cả danh mục", -1);
    comboLocLoai->addItem("Điện nước - Wifi", int(DIEN_NUOC_WIFI));
    comboLocLoai->addItem("Trọ - Ăn uống", int(TRO_AN_UONG));
    comboLocLoai->addItem("Khác", int(KHAC));

    dateLocTu = new QDateEdit(QDate::currentDate().addMonths(-1), khungLoc);
    dateLocTu->setCalendarPopup(true);

    dateLocDen = new QDateEdit(QDate::currentDate(), khungLoc);
    dateLocDen->setCalendarPopup(true);

    layoutLoc->addWidget(new QLabel("Danh mục:"));
    layoutLoc->addWidget(comboLocLoai);
    layoutLoc->addWidget(new QLabel("Từ ngày:"));
    layoutLoc->addWidget(dateLocTu);
    layoutLoc->addWidget(new QLabel("Đến ngày:"));
    layoutLoc->addWidget(dateLocDen);
    khungLoc->setLayout(layoutLoc);

    // ---- Bang danh sach ----
    bangGiaoDich = new QTableWidget(0, 3, this);
    bangGiaoDich->setHorizontalHeaderLabels({"Danh mục", "Số tiền", "Ngày"});
    bangGiaoDich->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    bangGiaoDich->setEditTriggers(QAbstractItemView::NoEditTriggers);

    layoutChinh->addLayout(layoutForm);
    layoutChinh->addWidget(khungLoc);
    layoutChinh->addWidget(bangGiaoDich);

    setLayout(layoutChinh);
}

void ThuNhapChiTieuWidget::ketNoiTinHieu() {
    connect(nutLuuThuNhap, &QPushButton::clicked, this, &ThuNhapChiTieuWidget::onLuuThuNhapClicked);
    connect(nutLuuChiTieu, &QPushButton::clicked, this, &ThuNhapChiTieuWidget::onLuuChiTieuClicked);
    connect(comboLocLoai, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ThuNhapChiTieuWidget::onLocThayDoi);
    connect(dateLocTu, &QDateEdit::dateChanged, this, &ThuNhapChiTieuWidget::onLocThayDoi);
    connect(dateLocDen, &QDateEdit::dateChanged, this, &ThuNhapChiTieuWidget::onLocThayDoi);
}

// ================= SLOTS =================

void ThuNhapChiTieuWidget::onLuuThuNhapClicked() {
    if (!nguoiDung) {
        QMessageBox::warning(this, "Lỗi", "Chưa có người dùng nào được chọn.");
        return;
    }

    QString loai = editLoaiThuNhap->text().trimmed();
    double soTien = spinSoTienThuNhap->value();

    if (loai.isEmpty()) {
        QMessageBox::warning(this, "Thiếu thông tin", "Vui lòng nhập loại thu nhập.");
        return;
    }
    if (!kiemTraHopLeSoTien(soTien)) return;

    ThuNhap tn(loai, soTien, dateThuNhap->date());
    nguoiDung->themThuNhap(tn);   // cong vao tong thang (RAM)
    repoThuNhap.them(tn);          // luu vinh vien vao SQLite

    editLoaiThuNhap->clear();
    spinSoTienThuNhap->setValue(0);
    dateThuNhap->setDate(QDate::currentDate());

    emit duLieuDaThayDoi();
    QMessageBox::information(this, "Thành công", "Đã lưu thu nhập.");
}

void ThuNhapChiTieuWidget::onLuuChiTieuClicked() {
    if (!nguoiDung) {
        QMessageBox::warning(this, "Lỗi", "Chưa có người dùng nào được chọn.");
        return;
    }

    LoaiChiTieu loai = static_cast<LoaiChiTieu>(comboLoaiChiTieu->currentData().toInt());
    double soTien = spinSoTienChiTieu->value();

    if (!kiemTraHopLeSoTien(soTien)) return;

    ChiTieu ct(loai, soTien, dateChiTieu->date());
    nguoiDung->themChiTieu(ct);   // cong vao tong thang (RAM)
    repoChiTieu.them(ct);          // luu vinh vien vao SQLite

    spinSoTienChiTieu->setValue(0);
    dateChiTieu->setDate(QDate::currentDate());

    onLocThayDoi(); // nap lai bang tu DB de thay giao dich vua them
    emit duLieuDaThayDoi();
    QMessageBox::information(this, "Thành công", "Đã lưu chi tiêu.");
}

void ThuNhapChiTieuWidget::onLocThayDoi() {
    QDate tuNgay = dateLocTu->date();
    QDate denNgay = dateLocDen->date();

    if (tuNgay > denNgay) {
        QMessageBox::warning(this, "Bộ lọc không hợp lệ", "\"Từ ngày\" phải nhỏ hơn hoặc bằng \"Đến ngày\".");
        return;
    }

    QList<ChiTieu> ketQua = repoChiTieu.locTheoKhoangThoiGian(tuNgay, denNgay);

    int locLoaiData = comboLocLoai->currentData().toInt();
    if (locLoaiData != -1) {
        LoaiChiTieu loaiCanLoc = static_cast<LoaiChiTieu>(locLoaiData);
        QList<ChiTieu> ketQuaSauLoc;
        for (const auto& ct : ketQua)
            if (ct.getLoai() == loaiCanLoc) ketQuaSauLoc.append(ct);
        ketQua = ketQuaSauLoc;
    }

    hienThiDanhSach(ketQua);
}

// ================= HAM HO TRO =================

void ThuNhapChiTieuWidget::hienThiDanhSach(const QList<ChiTieu>& danhSach) {
    bangGiaoDich->setRowCount(danhSach.size());
    for (int hang = 0; hang < danhSach.size(); ++hang) {
        const ChiTieu& ct = danhSach[hang];
        bangGiaoDich->setItem(hang, 0, new QTableWidgetItem(tenHienThi(ct.getLoai())));
        bangGiaoDich->setItem(hang, 1, new QTableWidgetItem(
            QString("%1 đ").arg(ct.getSoTien(), 0, 'f', 0)));
        bangGiaoDich->setItem(hang, 2, new QTableWidgetItem(ct.getNgay().toString("dd/MM/yyyy")));
    }
}

QString ThuNhapChiTieuWidget::tenHienThi(LoaiChiTieu loai) const {
    switch (loai) {
        case DIEN_NUOC_WIFI: return "Điện nước - Wifi";
        case TRO_AN_UONG:    return "Trọ - Ăn uống";
        case KHAC:           return "Khác";
    }
    return "Khác";
}

bool ThuNhapChiTieuWidget::kiemTraHopLeSoTien(double soTien) {
    if (soTien <= 0) {
        QMessageBox::warning(this, "Số tiền không hợp lệ", "Số tiền phải lớn hơn 0.");
        return false;
    }
    return true;
}
