#include "gui/mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile fileQss("style.qss");   // xem cách 2 bên dưới nếu chưa dùng .qrc
    if (fileQss.open(QFile::ReadOnly)) {
        a.setStyleSheet(QLatin1String(fileQss.readAll()));
    }
    return QApplication::exec();
}
