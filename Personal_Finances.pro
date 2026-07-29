QT += core gui sql charts

CONFIG += c++17

TARGET = QuanLyTaiChinh
TEMPLATE = app

INCLUDEPATH += $$PWD/src

SOURCES += \
    main.cpp \
    src/database/ChiTieuRepository.cpp \
    src/database/KetNoiDatabase.cpp \
    src/database/MucTieuRepository.cpp \
    src/database/NguoiDungRepository.cpp \
    src/database/ThuNhapRepository.cpp \
    src/goals/MucTieu.cpp \
    src/goals/MucTieuFactory.cpp \
    src/goals/MucTieuNganHan.cpp \
    src/goals/MucTieuDaiHan.cpp \
    src/models/ChiTieu.cpp \
    src/models/NguoiDung.cpp \
    src/models/ThuNhap.cpp \
    src/patterns/ChienLuocDaiHan.cpp \
    src/patterns/ChienLuocNganHan.cpp \
    src/patterns/TrangThaiChuaXong.cpp \
    src/patterns/TrangThaiHoanThanh.cpp \
    src/gui/mainwindow.cpp\
    src/gui/dashboardwidget.cpp \
    src/gui/thunhapchitieuwidget.cpp \
    src/gui/muctieuwidget.cpp \
    src/gui/bieudowidget.cpp \
    src/gui/goptietkiemdialog.cpp

HEADERS += \
    src/database/ChiTieuRepository.h \
    src/database/KetNoiDatabase.h \
    src/database/MucTieuRepository.h \
    src/database/NguoiDungRepository.h \
    src/database/ThuNhapRepository.h \
    src/goals/LoaiMucTieu.h \
    src/goals/MucTieu.h \
    src/goals/MucTieuFactory.h \
    src/goals/MucTieuNganHan.h \
    src/goals/MucTieuDaiHan.h \
    src/models/ChiTieu.h \
    src/models/NguoiDung.h \
    src/models/ThuNhap.h \
    src/patterns/ChienLuocDaiHan.h \
    src/patterns/ChienLuocNganHan.h \
    src/patterns/ChienLuocTietKiem.h \
    src/patterns/TrangThaiChuaXong.h \
    src/patterns/TrangThaiHoanThanh.h \
    src/patterns/TrangThaiMucTieu.h \
    src/gui/mainwindow.h\
    src/gui/dashboardwidget.h \
    src/gui/thunhapchitieuwidget.h \
    src/gui/muctieuwidget.h \
    src/gui/bieudowidget.h \
    src/gui/goptietkiemdialog.h


FORMS += \
    src/gui/mainwindow.ui\
    src/gui/dashboardwidget.ui \
    src/gui/thunhapchitieuwidget.ui \
    src/gui/muctieuwidget.ui \
    src/gui/bieudowidget.ui \
    src/gui/goptietkiemdialog.ui

RESOURCES += \
    resources/icons.qrc \
    resources/icons.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target