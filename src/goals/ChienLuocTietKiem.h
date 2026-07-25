#ifndef CHIENLUOCTIETKIEM_H
#define CHIENLUOCTIETKIEM_H

// Đây là Interface (Lớp giao diện) trong C++
class ChienLuocTietKiem {
public:
    virtual ~ChienLuocTietKiem() {}

    // Hàm thuần ảo: Phân bổ tiền tiết kiệm
    virtual void phanBoTien(double soTien) = 0;
};

#endif // CHIENLUOCTIETKIEM_H