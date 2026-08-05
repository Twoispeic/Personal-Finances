#include "LoginController.h"
#include "database/NguoiDungRepository.h"
#include "database/KetNoiDatabase.h"

bool LoginController::dangNhap(const QString& taiKhoan, const QString& matKhau) {
    NguoiDungRepository repo;
    repo.taoBang();
    int id = repo.dangNhap(taiKhoan, matKhau);
    if (id > 0) {
        KetNoiDatabase::getInstance().chuyenSangDuLieuTaiKhoan(taiKhoan);
        emit dangNhapThanhCong(id);
        return true;
    }
    emit dangNhapThatBai("Sai tài khoản hoặc mật khẩu.");
    return false;
}

bool LoginController::dangKy(const QString& taiKhoan, const QString& matKhau, const QString& ten) {
    NguoiDungRepository repo;
    repo.taoBang();
    int id = repo.dangKy(taiKhoan, matKhau, ten);
    if (id > 0) {
        // MỚI: tài khoản mới -> tạo/mở luôn file dữ liệu riêng cho tài khoản này
        KetNoiDatabase::getInstance().chuyenSangDuLieuTaiKhoan(taiKhoan);
        emit dangNhapThanhCong(id); // đăng ký xong thì coi như đăng nhập luôn
        return true;
    }
    emit dangNhapThatBai("Tài khoản đã tồn tại hoặc thông tin không hợp lệ.");
    return false;
}
