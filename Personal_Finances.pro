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
    src/gui/DashboardWidget.cpp \
    src/gui/MucTieuWidget.cpp \
    src/gui/ThuNhapChiTieuWidget.cpp \
    src/gui/bieudowidget.cpp \
    src/gui/bieudowidget.cpp \
    src/gui/goptietkiemdialog.cpp \
    src/gui/goptietkiemdialog.cpp \
    src/gui/input/quanlychitieuwidget.cpp \
    src/gui/input/themchitieudialog.cpp \
    src/gui/input/thunhapcanhanwidget.cpp \
    src/gui/input/trangchuwidget.cpp \
    src/gui/muctieucardwidget.cpp \
    src/gui/muctieutaichinhwidget.cpp \
    src/gui/quanlychitieuwidget.cpp \
    src/gui/sidebarwidget.cpp \
    src/gui/sidebarwidget.cpp \
    src/gui/taomuctieudialog.cpp \
    src/gui/themchitieudialog.cpp \
    src/gui/thunhapcanhanwidget.cpp \
    src/gui/trangchuwidget.cpp \
    src/models/ChiTieu.cpp \
    src/models/NguoiDung.cpp \
    src/models/ThuNhap.cpp \
    src/patterns/ChienLuocDaiHan.cpp \
    src/patterns/ChienLuocNganHan.cpp \
    src/patterns/TrangThaiChuaXong.cpp \
    src/patterns/TrangThaiHoanThanh.cpp \
    src/widgets/GopTietKiemDialog.cpp \
    src/widgets/MucTieuWidget.cpp\
    src/gui/mainwindow.cpp\
    src/gui/dashboardwidget.cpp \
    src/gui/thunhapchitieuwidget.cpp \
    src/gui/muctieuwidget.cpp \
    src/gui/bieudowidget.cpp \
    src/gui/goptietkiemdialog.cpp\
    src/widgets/MucTieuWidget.cpp \
    src/widgets/GopTietKiemDialog.cpp \
    src/widgets/MucTieuWidget.cpp \
    src/widgets/GopTietKiemDialog.cpp \
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
    src/gui/goals/goptietkiemdialog.cpp
HEADERS +=\
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
    src/gui/DashboardWidget.h \
    src/gui/MucTieuWidget.h \
    src/gui/ThuNhapChiTieuWidget.h \
    src/gui/bieudowidget.h \
    src/gui/bieudowidget.h \
    src/gui/goptietkiemdialog.h \
    src/gui/goptietkiemdialog.h \
    src/gui/input/quanlychitieuwidget.h \
    src/gui/input/themchitieudialog.h \
    src/gui/input/thunhapcanhanwidget.h \
    src/gui/input/trangchuwidget.h \
    src/gui/muctieucardwidget.h \
    src/gui/muctieutaichinhwidget.h \
    src/gui/quanlychitieuwidget.h \
    src/gui/sidebarwidget.h \
    src/gui/sidebarwidget.h \
    src/gui/taomuctieudialog.h \
    src/gui/themchitieudialog.h \
    src/gui/thunhapcanhanwidget.h \
    src/gui/trangchuwidget.h \
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
    src/gui/goptietkiemdialog.h \
    src/widgets/GopTietKiemDialog.h \
    src/widgets/MucTieuWidget.h\
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
    src/gui/goals/goptietkiemdialog.h
FORMS +=\
    src/gui/goals/muctieutaichinhwidget.ui \
    src/gui/mainwindow.ui \
    src/gui/sidebarwidget.ui \
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
RESOURCES += \
    resources/icons.qrc \
    resources/icons.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target