#ifndef CHIENLUOCTIETKIEM_H
#define CHIENLUOCTIETKIEM_H

class ChienLuocTietKiem {
public:
    virtual ~ChienLuocTietKiem() {}
    virtual double phanBoTien(double soTienDu, double soTienConThieu) = 0;
};

#endif // CHIENLUOCTIETKIEM_H
