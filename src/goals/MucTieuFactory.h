/*#ifndef MUCTIEUFACTORY_H
#define MUCTIEUFACTORY_H

#include <QString>

class MucTieu;   // forward declaration — chỉ trả về con trỏ, không cần include đầy đủ ở .h

class MucTieuFactory {
public:
    static MucTieu* taoMucTieuNganHan(const QString& ten, double soTienMucTieu, int thoiHanThang);
    static MucTieu* taoMucTieuDaiHan(const QString& ten, double soTienMucTieu, int soKyTraGop);
};

#endif
*/