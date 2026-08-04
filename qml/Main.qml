// Main.qml — khung + điều hướng hoàn chỉnh
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Effects

ApplicationWindow {
    visible: true
    width: 1000
    height: 650
    color: "#12172B"
    title: "Quản lý tài chính"

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // THANH SIDEBAR BÊN TRÁI
        Rectangle {
            Layout.preferredWidth: 220
            Layout.fillHeight: true
            color: "#0D111F"

            ColumnLayout {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 16
                spacing: 8

                // Dùng Repeater để render danh sách nút Sidebar (Khắc phục hoàn toàn lỗi không click được)
                Repeater {
                    model: ListModel {
                        ListElement { ten: "Trang chủ"; iconPath: "qrc:/icons/icons/home.svg" }
                        ListElement { ten: "Quản lý chi tiêu"; iconPath: "qrc:/icons/icons/wallet.svg" }
                        ListElement { ten: "Thu nhập cá nhân"; iconPath: "qrc:/icons/icons/income.svg" }
                        ListElement { ten: "Mục tiêu tài chính"; iconPath: "qrc:/icons/icons/target.svg" }
                    }
                    delegate: Rectangle {
                        Layout.fillWidth: true
                        height: 48
                        radius: 12
                        color: stack.currentIndex === index ? "#1B1E42" : "transparent"

                        RowLayout {
                                                    anchors.fill: parent
                                                    anchors.leftMargin: 16
                                                    spacing: 12

                                                    // 1. Bọc Image và MultiEffect vào 1 Item để Layout không bị lỗi
                                                    Item {
                                                        Layout.preferredWidth: 20
                                                        Layout.preferredHeight: 20
                                                        Layout.alignment: Qt.AlignVCenter // CĂN GIỮA DỌC CHO ICON

                                                        Image {
                                                            id: imgIcon
                                                            anchors.fill: parent
                                                            source: model.iconPath
                                                            visible: false // Ẩn ảnh gốc
                                                        }

                                                        MultiEffect {
                                                            anchors.fill: parent
                                                            source: imgIcon
                                                            colorization: 1.0
                                                            colorizationColor: stack.currentIndex === index ? "#35DDC0" : "#5F638F"
                                                        }
                                                    }

                                                    // 2. Thêm căn giữa dọc cho Text
                                                    Text {
                                                        text: model.ten
                                                        color: stack.currentIndex === index ? "#35DDC0" : "#5F638F"
                                                        font.pixelSize: 15; font.bold: stack.currentIndex === index
                                                        Layout.alignment: Qt.AlignVCenter // CĂN GIỮA DỌC CHO TEXT
                                                    }
                                                }

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: stack.currentIndex = index
                        }
                    }
                }
            }
        }

        // KHU VỰC HIỂN THỊ CÁC TRANG (STACK)
        StackLayout {
            id: stack
            Layout.fillWidth: true
            Layout.fillHeight: true

            TrangChuPage {}
            QuanLyChiTieuPage {}
            ThuNhapPage {}
            MucTieuPage {}
        }
    }

    XacNhanChotSoDialog {
        id: xacNhanChotSoDialog
    }
}