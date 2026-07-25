#ifndef NGUOIDUNG_H
#define NGUOIDUNG_H

#include <QString>

class NguoiDung {
private:
    QString ten;
    QString congViec;

public:
    NguoiDung();
    NguoiDung(QString tenND, QString congViecND);

    QString getTen() const;
    void setTen(const QString &tenND);

    QString getCongViec() const;
    void setCongViec(const QString &congViecND);
};

#endif // NGUOIDUNG_H