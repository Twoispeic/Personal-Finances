#include "MucTieuRepository.h"
#include "KetNoiDatabase.h"
#include "src/goals/MucTieuNganHan.h"
#include "src/goals/MucTieuDaiHan.h"
#include "src/goals/MucTieu.h"
#include "src/patterns/TrangThaiChuaXong.h"
#include "src/patterns/TrangThaiHoanThanh.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

MucTieuRepository::MucTieuRepository() {}

bool MucTieuRepository::taoBang() {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;

    QSqlQuery query;
    QString sql = "CREATE TABLE IF NOT EXISTS MucTieu ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "loaiMucTieu TEXT, "
                  "tenMucTieu TEXT, "
                  "soTienMucTieu REAL, "
                  "soTienDaTietKiem REAL, "
                  "trangThai TEXT, "
                  "thoiHanThang INTEGER, "
                  "soKyTraGop INTEGER, "
                  "soTienMoiKy REAL, "
                  "soKyDaTra INTEGER DEFAULT 0, "
                  "thangNamDaTra TEXT DEFAULT '', "
                  "soTienMocAnToan REAL DEFAULT -1)";
    bool ok = query.exec(sql);

    QSqlQuery migrate;
    migrate.exec("ALTER TABLE MucTieu ADD COLUMN soKyDaTra INTEGER DEFAULT 0");
    migrate.exec("ALTER TABLE MucTieu ADD COLUMN thangNamDaTra TEXT DEFAULT ''");
    migrate.exec("ALTER TABLE MucTieu ADD COLUMN soTienMocAnToan REAL DEFAULT -1");

    return ok;
}

bool MucTieuRepository::them(MucTieu* mucTieu) {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;

    QSqlQuery query;
    MucTieuNganHan* ngan = dynamic_cast<MucTieuNganHan*>(mucTieu);
    MucTieuDaiHan* dai = dynamic_cast<MucTieuDaiHan*>(mucTieu);

    query.prepare("INSERT INTO MucTieu "
                  "(loaiMucTieu, tenMucTieu, soTienMucTieu, soTienDaTietKiem, trangThai, thoiHanThang, soKyTraGop, soTienMoiKy, "
                  "soKyDaTra, thangNamDaTra, soTienMocAnToan) "
                  "VALUES (:loai, :ten, :soTienMT, :soTienDTK, :trangThai, :thoiHan, :soKy, :soTienKy, "
                  ":soKyDaTra, :thangNamDaTra, :soTienMocAnToan)");

    query.bindValue(":ten", mucTieu->getTenMucTieu());
    query.bindValue(":soTienMT", mucTieu->getSoTienMucTieu());
    query.bindValue(":soTienDTK", mucTieu->getSoTienDaTietKiem());
    query.bindValue(":trangThai", mucTieu->layMauSacHienTai() == "green" ? "HoanThanh" : "ChuaXong");

    if (ngan != nullptr) {
        query.bindValue(":loai", "NganHan");
        query.bindValue(":thoiHan", ngan->getThoiHanThang());
        query.bindValue(":soKy", QVariant());
        query.bindValue(":soTienKy", QVariant());
        query.bindValue(":soKyDaTra", QVariant());
        query.bindValue(":thangNamDaTra", QVariant());
        query.bindValue(":soTienMocAnToan", QVariant());
    } else if (dai != nullptr) {
        query.bindValue(":loai", "DaiHan");
        query.bindValue(":thoiHan", QVariant());
        query.bindValue(":soKy", dai->getSoKyTraGop());
        query.bindValue(":soTienKy", dai->getSoTienMoiKy());
        // Mục tiêu dài hạn mới tạo: chưa từng trả góp -> 0 kỳ, chưa có tháng, chưa có mốc an toàn
        query.bindValue(":soKyDaTra", 0);
        query.bindValue(":thangNamDaTra", "");
        query.bindValue(":soTienMocAnToan", -1.0);
    }

    bool ok = query.exec();
    if (!ok) qWarning() << "[MucTieuRepository::them] Loi INSERT:" << query.lastError().text();
    return ok;
}

bool MucTieuRepository::capNhatTienDaTietKiem(int id, double soTienMoi) {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;

    QSqlQuery query;
    query.prepare("UPDATE MucTieu SET soTienDaTietKiem = :soTien WHERE id = :id");
    query.bindValue(":soTien", soTienMoi);
    query.bindValue(":id", id);
    return query.exec();
}

QList<MucTieu*> MucTieuRepository::layTatCa() {
    QList<MucTieu*> ketQua;
    if (!KetNoiDatabase::getInstance().moKetNoi()) return ketQua;

    QSqlQuery query("SELECT id,loaiMucTieu, tenMucTieu, soTienMucTieu, soTienDaTietKiem, "
                    "trangThai, thoiHanThang, soKyTraGop, soTienMoiKy, "
                    "soKyDaTra, thangNamDaTra, soTienMocAnToan FROM MucTieu");

    while (query.next()) {
        int id = query.value("id").toInt();
        QString loai = query.value("loaiMucTieu").toString();
        QString ten = query.value("tenMucTieu").toString();
        double soTienMT = query.value("soTienMucTieu").toDouble();
        double soTienDTK = query.value("soTienDaTietKiem").toDouble();
        QString trangThai = query.value("trangThai").toString();

        MucTieu* mt = nullptr;
        if (loai == "NganHan") {
            int thoiHan = query.value("thoiHanThang").toInt();
            mt = MucTieu::taoMucTieuNganHan(ten, soTienMT, thoiHan);
        } else {
            int soKy = query.value("soKyTraGop").toInt();
            mt = MucTieu::taoMucTieuDaiHan(ten, soTienMT, soKy);

            // QUAN TRỌNG: nạp lại trạng thái trả góp theo tháng từ DB — nếu thiếu bước này,
            // mỗi lần layTatCa() sẽ tạo object DaiHan với giá trị MẶC ĐỊNH (soKyDaTra=0,
            // thangNamDaTra="", soTienMocAnToan=-1), khiến app luôn nghĩ "chưa từng trả góp"
            // dù thực tế DB đã có dữ liệu, và làm khoá "1 lần/tháng" không bao giờ hoạt động.
            MucTieuDaiHan* dai = static_cast<MucTieuDaiHan*>(mt);
            dai->setSoKyDaTra(query.value("soKyDaTra").toInt());
            dai->setThangNamDaTra(query.value("thangNamDaTra").toString());
            QVariant mocRaw = query.value("soTienMocAnToan");
            dai->setSoTienMocAnToan(mocRaw.isNull() ? -1.0 : mocRaw.toDouble());
        }
        mt->datId(id);
        mt->datSoTienDaTietKiem(soTienDTK);   // nạp lại tiến độ, không tính lại qua Strategy
        if (mt->kiemTraHoanThanh()) {
            mt->datTrangThai(new TrangThaiHoanThanh());
        } else {
            mt->datTrangThai(new TrangThaiChuaXong());
        }
        ketQua.append(mt);
    }
    return ketQua;
}
bool MucTieuRepository::xoa(int id) {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;
    QSqlQuery q; q.prepare("DELETE FROM MucTieu WHERE id = :id"); q.bindValue(":id", id);
    return q.exec();
}

bool MucTieuRepository::capNhatTrangThaiThang(int id, double soTienDaTietKiemMoi, int soKyDaTraMoi,
                                              const QString& thangNamDaTraMoi, double soTienMocAnToanMoi) {
    if (!KetNoiDatabase::getInstance().moKetNoi()) return false;

    QSqlQuery query;
    query.prepare("UPDATE MucTieu SET soTienDaTietKiem = :soTien, soKyDaTra = :soKy, "
                  "thangNamDaTra = :thangNam, soTienMocAnToan = :moc WHERE id = :id");
    query.bindValue(":soTien", soTienDaTietKiemMoi);
    query.bindValue(":soKy", soKyDaTraMoi);
    query.bindValue(":thangNam", thangNamDaTraMoi);
    query.bindValue(":moc", soTienMocAnToanMoi);
    query.bindValue(":id", id);
    bool ok = query.exec();
    if (!ok) qWarning() << "[MucTieuRepository::capNhatTrangThaiThang] Loi UPDATE:" << query.lastError().text();
    return ok;
}