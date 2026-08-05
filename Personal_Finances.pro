QT += core gui sql qml quick quickcontrols2 charts
CONFIG += c++17
TARGET = QuanLyTaiChinh
TEMPLATE = app

INCLUDEPATH += $$PWD/src

SOURCES += \
    main.cpp \
    src/controller/AppController.cpp \
    src/controller/ChiTieuController.cpp \
    src/controller/MucTieuController.cpp \
    src/controller/ThuNhapController.cpp \
    src/database/ChiTieuRepository.cpp \
    src/database/KetNoiDatabase.cpp \
    src/database/MucTieuRepository.cpp \
    src/database/NgayMoPhong.cpp \
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
    src/patterns/TrangThaiHoanThanh.cpp

HEADERS += \
    src/controller/AppController.h \
    src/controller/ChiTieuController.h \
    src/controller/MucTieuController.h \
    src/controller/ThuNhapController.h \
    src/database/ChiTieuRepository.h \
    src/database/KetNoiDatabase.h \
    src/database/MucTieuRepository.h \
    src/database/NgayMoPhong.h \
    src/database/NguoiDungRepository.h \
    src/database/ThuNhapRepository.h \
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
    src/patterns/TrangThaiMucTieu.h\
    src/utils/MatKhauUtil.h

RESOURCES += \
    qml/qml.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target