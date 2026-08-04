#ifndef MATKHAUUTIL_H
#define MATKHAUUTIL_H
#include <QString>
#include <QCryptographicHash>
#include <QRandomGenerator>

class MatKhauUtil {
public:
    static QString taoSalt() {
        QString salt;
        for (int i = 0; i < 16; ++i)
            salt += QString::number(QRandomGenerator::global()->bounded(16), 16);
        return salt;
    }

    static QString hash(const QString& matKhau, const QString& salt) {
        QByteArray data = (matKhau + salt).toUtf8();
        return QCryptographicHash::hash(data, QCryptographicHash::Sha256).toHex();
    }
};
#endif // MATKHAUUTIL_H