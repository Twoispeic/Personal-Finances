#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle> // BỔ SUNG: Dùng để ép style QML
#include <QQmlEngine>  // BỔ SUNG: Dùng để đăng ký Type

#include "controller/AppController.h"
#include "controller/ChiTieuController.h" // Khai báo thêm để QML biết
#include "controller/ThuNhapController.h" // Khai báo thêm để QML biết
#include "controller/MucTieuController.h" // Khai báo thêm để QML biết
#include "controller/LoginController.h"   // THÊM MỚI: cho màn hình đăng nhập
#include "database/KetNoiDatabase.h"

int main(int argc, char *argv[]) {
    // Ép QML dùng style Basic để cho phép đổi màu nút, bo góc thoải mái
    QQuickStyle::setStyle("Basic");

    QGuiApplication app(argc, argv);

    KetNoiDatabase::getInstance().moKetNoi();

    QQmlApplicationEngine engine;

    // Đăng ký các class Controller con để QML nhận diện được con trỏ (chữa lỗi null)
    qmlRegisterUncreatableType<ChiTieuController>("SoTayTien", 1, 0, "ChiTieuController", "Khong the tao truc tiep");
    qmlRegisterUncreatableType<ThuNhapController>("SoTayTien", 1, 0, "ThuNhapController", "Khong the tao truc tiep");
    qmlRegisterUncreatableType<MucTieuController>("SoTayTien", 1, 0, "MucTieuController", "Khong the tao truc tiep");

    AppController controller;
    engine.rootContext()->setContextProperty("appController", &controller);

    // THÊM MỚI: LoginController cho màn hình đăng nhập/đăng ký
    LoginController loginController;
    engine.rootContext()->setContextProperty("loginController", &loginController);

    const QUrl url(QStringLiteral("qrc:/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}