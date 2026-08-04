// src/controller/LoginController.h
#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H
#include <QObject>

class LoginController : public QObject {
    Q_OBJECT
public:
    explicit LoginController(QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE bool dangNhap(const QString& taiKhoan, const QString& matKhau);
    Q_INVOKABLE bool dangKy(const QString& taiKhoan, const QString& matKhau, const QString& ten);

signals:
    void dangNhapThanhCong(int nguoiDungId);
    void dangNhapThatBai(QString lyDo);
};
#endif