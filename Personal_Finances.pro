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
    src/gui/mainwindow.cpp \
    src/gui/sidebarwidget.cpp \
    src/gui/input/trangchuwidget.cpp \
    src/gui/input/quanlychitieuwidget.cpp \
    src/gui/input/thunhapcanhanwidget.cpp \
    src/gui/input/bieudowidget.cpp \
    src/gui/input/themchitieudialog.cpp \
    src/gui/goals/muctieutaichinhwidget.cpp \
    src/gui/goals/muctieucardwidget.cpp \
    src/gui/goals/taomuctieudialog.cpp \
    src/gui/goals/goptietkiemdialog.cpp \
    src/models/ChiTieu.cpp \
    src/models/NguoiDung.cpp \
    src/models/ThuNhap.cpp \
    src/patterns/ChienLuocDaiHan.cpp \
    src/patterns/ChienLuocNganHan.cpp \
    src/patterns/TrangThaiChuaXong.cpp \
    src/patterns/TrangThaiHoanThanh.cpp

HEADERS += \
    src/database/ChiTieuRepository.h \
    src/database/KetNoiDatabase.h \
    src/database/MucTieuRepository.h \
    src/database/NguoiDungRepository.h \
    src/database/ThuNhapRepository.h \
    src/goals/MucTieu.h \
    src/goals/MucTieuFactory.h \
    src/goals/MucTieuNganHan.h \
    src/goals/MucTieuDaiHan.h \
    src/gui/mainwindow.h \
    src/gui/sidebarwidget.h \
    src/gui/input/trangchuwidget.h \
    src/gui/input/quanlychitieuwidget.h \
    src/gui/input/thunhapcanhanwidget.h \
    src/gui/input/bieudowidget.h \
    src/gui/input/themchitieudialog.h \
    src/gui/goals/muctieutaichinhwidget.h \
    src/gui/goals/muctieucardwidget.h \
    src/gui/goals/taomuctieudialog.h \
    src/gui/goals/goptietkiemdialog.h \
    src/models/ChiTieu.h \
    src/models/NguoiDung.h \
    src/models/ThuNhap.h \
    src/patterns/ChienLuocDaiHan.h \
    src/patterns/ChienLuocNganHan.h \
    src/patterns/ChienLuocTietKiem.h \
    src/patterns/TrangThaiChuaXong.h \
    src/patterns/TrangThaiHoanThanh.h \
    src/patterns/TrangThaiMucTieu.h

FORMS += \
    src/gui/mainwindow.ui \
    src/gui/sidebarwidget.ui \
    src/gui/input/trangchuwidget.ui \
    src/gui/input/quanlychitieuwidget.ui \
    src/gui/input/thunhapcanhanwidget.ui \
    src/gui/input/bieudowidget.ui \
    src/gui/input/themchitieudialog.ui \
    src/gui/goals/muctieutaichinhwidget.ui \
    src/gui/goals/muctieucardwidget.ui \
    src/gui/goals/taomuctieudialog.ui \
    src/gui/goals/goptietkiemdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target