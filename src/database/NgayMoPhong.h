// .h
#ifndef NGAYMOPHONG_H
#define NGAYMOPHONG_H
#include <QDate>

// Singleton (Meyer's Singleton — cùng kỹ thuật với KetNoiDatabase::getInstance()):
// chỉ 1 instance duy nhất tồn tại trong suốt vòng đời app, truy cập qua getInstance().
class NgayMoPhong {
public:
    static NgayMoPhong& getInstance();

    void datTaiKhoanHienTai(int idNguoiDung);
    QDate layNgayHienTai();
    QDate quaThangMoi();

private:
    NgayMoPhong() = default;                              // constructor PRIVATE — không ai new được từ bên ngoài
    NgayMoPhong(const NgayMoPhong&) = delete;              // cấm copy — đảm bảo chỉ có 1 instance
    NgayMoPhong& operator=(const NgayMoPhong&) = delete;

    // id = 0 nghĩa là "chưa đăng nhập tài khoản nào" (fallback an toàn, không vỡ code cũ).
    // Mỗi tài khoản có id riêng (AUTOINCREMENT, không bao giờ trùng/tái sử dụng) nên dùng id
    // làm hậu tố key là đủ để đảm bảo tài khoản mới KHÔNG đọc nhầm tháng mô phỏng của tài khoản khác.
    int idTaiKhoanHienTai = 0;

    QString khoaThangMoPhong() const;
};
#endif