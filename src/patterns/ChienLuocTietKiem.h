#ifndef CHIENLUOCTIETKIEM_H
#define CHIENLUOCTIETKIEM_H

//Strategy
class ChienLuocTietKiem
{
public:
    virtual ~ChienLuocTietKiem();
    virtual double phanBoTien(double soTienDu)=0;
};

#endif // CHIENLUOCTIETKIEM_H
