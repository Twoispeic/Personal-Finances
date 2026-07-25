#include "NguoiDung.h"

NguoiDung::NguoiDung() {
    this->ten = "";
    this->congViec = "";
}

NguoiDung::NguoiDung(QString tenND, QString congViecND) {
    this->ten = tenND;
    this->congViec = congViecND;
}

QString NguoiDung::getTen() const { return ten; }
void NguoiDung::setTen(const QString &tenND) { this->ten = tenND; }

QString NguoiDung::getCongViec() const { return congViec; }
void NguoiDung::setCongViec(const QString &congViecND) { this->congViec = congViecND; }