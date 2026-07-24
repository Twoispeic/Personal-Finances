QT       += core gui widgets sql charts

CONFIG   += c++17

TARGET   = QuanLyTaiChinh
TEMPLATE = app

SOURCES += \
    main.cpp \
    src/database/KetNoiDatabase.cpp \
    src/goals/MucTieu.cpp \
    src/goals/MucTieuNganHan.cpp \
    src/models/NguoiDung.cpp \
    src/models/ThuNhap.cpp \
    src/models/ThuNhap.cpp \
    src/models/ChiTieu.cpp \
    src/goals/MucTieu.cpp \
    src/goals/MucTieuNganHan.cpp \
    src/goals/MucTieuDaiHan.cpp \
    src/goals/MucTieuFactory.cpp \
    src/patterns/ChienLuocDaiHan.cpp \
    src/patterns/ChienLuocNganHan.cpp \
    src/patterns/ChienLuocNganHan.cpp \
    src/patterns/TrangThaiChuaXong.cpp \
    src/patterns/TrangThaiChuaXong.cpp \
    src/patterns/TrangThaiHoanThanh.cpp \
    src/patterns/TrangThaiHoanThanh.cpp \
    src/database/KetNoiDatabase.cpp \
    src/database/NguoiDungRepository.cpp \
    src/database/ThuNhapRepository.cpp \
    src/database/ChiTieuRepository.cpp \
    src/database/MucTieuRepository.cpp \
    src/gui/mainwindow.cpp \
    src/gui/DashboardWidget.cpp \
    src/gui/ThuNhapChiTieuWidget.cpp \
    src/gui/MucTieuWidget.cpp \
    src/gui/BieuDoWidget.cpp

HEADERS += \
    src/database/KetNoiDatabase.h \
    src/goals/MucTieu.h \
    src/goals/MucTieuNganHan.h \
    src/models/NguoiDung.h \
    src/models/ThuNhap.h \
    src/models/ThuNhap.h \
    src/models/ChiTieu.h \
    src/models/LoaiChiTieu.h \
    src/goals/MucTieu.h \
    src/goals/MucTieuNganHan.h \
    src/goals/MucTieuDaiHan.h \
    src/goals/MucTieuFactory.h \
    src/patterns/ChienLuocDaiHan.h \
    src/patterns/ChienLuocNganHan.h \
    src/patterns/ChienLuocTietKiem.h \
    src/patterns/ChienLuocTietKiem.h \
    src/patterns/ChienLuocNganHan.h \
    src/patterns/TrangThaiChuaXong.h \
    src/patterns/TrangThaiHoanThanh.h \
    src/patterns/TrangThaiMucTieu.h \
    src/patterns/TrangThaiMucTieu.h \
    src/patterns/TrangThaiChuaXong.h \
    src/patterns/TrangThaiHoanThanh.h \
    src/database/KetNoiDatabase.h \
    src/database/NguoiDungRepository.h \
    src/database/ThuNhapRepository.h \
    src/database/ChiTieuRepository.h \
    src/database/MucTieuRepository.h \
    src/gui/mainwindow.h \
    src/gui/DashboardWidget.h \
    src/gui/ThuNhapChiTieuWidget.h \
    src/gui/MucTieuWidget.h \
    src/gui/BieuDoWidget.h

FORMS += \
    src/gui/mainwindow.ui \
    src/gui/DashboardWidget.ui \
    src/gui/ThuNhapChiTieuWidget.ui \
    src/gui/MucTieuWidget.ui \
    src/gui/BieuDoWidget.ui

RESOURCES += \
    resources/icons.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
