#include "NguoiDungRepository.h"
#include "KetNoiDatabase.h"
#include "utils/MatKhauUtil.h"
NguoiDungRepository::NguoiDungRepository() {}

// LƯU Ý: Repository này CỐ TÌNH dùng KetNoiDatabase::moKetNoiTaiKhoan() (1 connection RIÊNG,
// CỐ ĐỊNH, không đổi theo ai đang đăng nhập) thay vì connection mặc định — vì phải tra được
// tài khoản/mật khẩu TRƯỚC KHI biết nên mở file dữ liệu tài chính nào cho đúng người.
// Nhờ vậy ChiTieuRepository/ThuNhapRepository/MucTieuRepository không cần sửa gì cả.

bool NguoiDungRepository::taoBang() {
    QSqlDatabase db = KetNoiDatabase::moKetNoiTaiKhoan();
    if (!db.isOpen()) return false;

    QSqlQuery query(db);
    QString sql = "CREATE TABLE IF NOT EXISTS NguoiDung ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "ten TEXT, "
                  "congViec TEXT, "
                  "taiKhoan TEXT, "
                  "matKhauHash TEXT, "
                  "salt TEXT)";
    bool ok = query.exec(sql);

    // Migrate DB cũ (đã tạo bảng NguoiDung từ trước, chưa có cột tài khoản/mật khẩu).
    // exec() sẽ báo lỗi (bị bỏ qua) nếu cột đã tồn tại rồi — vô hại, không cần xử lý.
    QSqlQuery(db).exec("ALTER TABLE NguoiDung ADD COLUMN taiKhoan TEXT");
    QSqlQuery(db).exec("ALTER TABLE NguoiDung ADD COLUMN matKhauHash TEXT");
    QSqlQuery(db).exec("ALTER TABLE NguoiDung ADD COLUMN salt TEXT");

    return ok;
}

bool NguoiDungRepository::luuNguoiDung(const NguoiDung &nguoiDung) {
    QSqlDatabase db = KetNoiDatabase::moKetNoiTaiKhoan();
    if (!db.isOpen()) return false;

    QSqlQuery kiemTra(db);
    kiemTra.exec("SELECT COUNT(*) FROM NguoiDung");
    kiemTra.next();
    bool daCoDuLieu = kiemTra.value(0).toInt() > 0;

    QSqlQuery query(db);
    if (daCoDuLieu) {
        query.prepare("UPDATE NguoiDung SET ten = :ten, congViec = :congViec WHERE id = 1");
    } else {
        query.prepare("INSERT INTO NguoiDung (ten, congViec) VALUES (:ten, :congViec)");
    }
    query.bindValue(":ten", nguoiDung.getTen());
    query.bindValue(":congViec", nguoiDung.getCongViec());
    return query.exec();
}

NguoiDung NguoiDungRepository::layThongTinNguoiDung() {
    NguoiDung nd;
    QSqlDatabase db = KetNoiDatabase::moKetNoiTaiKhoan();
    if (!db.isOpen()) return nd;

    QSqlQuery query(db);
    query.exec("SELECT ten, congViec FROM NguoiDung LIMIT 1");
    if (query.next()) {
        nd.setTen(query.value("ten").toString());
        nd.setCongViec(query.value("congViec").toString());
    }
    return nd;
}

// ===== BỔ SUNG cho đăng nhập/đăng ký =====

int NguoiDungRepository::dangKy(const QString& taiKhoan, const QString& matKhau, const QString& ten) {
    QSqlDatabase db = KetNoiDatabase::moKetNoiTaiKhoan();
    if (!db.isOpen()) return -1;
    if (taiKhoan.trimmed().isEmpty() || matKhau.isEmpty()) return -1;

    QSqlQuery kiemTra(db);
    kiemTra.prepare("SELECT id FROM NguoiDung WHERE taiKhoan = :tk");
    kiemTra.bindValue(":tk", taiKhoan);
    kiemTra.exec();
    if (kiemTra.next()) return -1; // tài khoản đã tồn tại

    QString salt = MatKhauUtil::taoSalt();
    QString hash = MatKhauUtil::hash(matKhau, salt);

    QSqlQuery them(db);
    them.prepare("INSERT INTO NguoiDung (ten, congViec, taiKhoan, matKhauHash, salt) "
                 "VALUES (:ten, '', :tk, :hash, :salt)");
    them.bindValue(":ten", ten);
    them.bindValue(":tk", taiKhoan);
    them.bindValue(":hash", hash);
    them.bindValue(":salt", salt);
    if (!them.exec()) return -1;

    return them.lastInsertId().toInt();
}

int NguoiDungRepository::dangNhap(const QString& taiKhoan, const QString& matKhau) {
    QSqlDatabase db = KetNoiDatabase::moKetNoiTaiKhoan();
    if (!db.isOpen()) return -1;

    QSqlQuery query(db);
    query.prepare("SELECT id, matKhauHash, salt FROM NguoiDung WHERE taiKhoan = :tk");
    query.bindValue(":tk", taiKhoan);
    query.exec();
    if (!query.next()) return -1;

    QString hashLuu = query.value("matKhauHash").toString();
    QString salt = query.value("salt").toString();
    if (hashLuu.isEmpty() || MatKhauUtil::hash(matKhau, salt) != hashLuu) return -1;

    return query.value("id").toInt();
}

NguoiDung NguoiDungRepository::layThongTinTheoId(int id) {
    NguoiDung nd;
    QSqlDatabase db = KetNoiDatabase::moKetNoiTaiKhoan();
    if (!db.isOpen()) return nd;

    QSqlQuery query(db);
    query.prepare("SELECT ten, congViec FROM NguoiDung WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
    if (query.next()) {
        nd.setTen(query.value("ten").toString());
        nd.setCongViec(query.value("congViec").toString());
    }
    return nd;
}
