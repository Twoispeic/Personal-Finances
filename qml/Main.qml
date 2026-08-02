import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ApplicationWindow {
    id: root
    visible: true
    width: 1280
    height: 720
    title: qsTr("Sổ Tay Tiền")

    // Màu nền tổng thể từ mockup
    color: "#12142B"

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // ============ SIDEBAR ============
        Rectangle {
            Layout.preferredWidth: 236
            Layout.fillHeight: true
            color: "#0C0E22"

            // Viền phải
            Rectangle {
                width: 1
                height: parent.height
                anchors.right: parent.right
                color: "#12FFFFFF"
            }

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 12

                // Logo
                RowLayout {
                    spacing: 10
                    Rectangle {
                        width: 12; height: 12; radius: 6
                        color: "#35DDC0"
                    }
                    Text {
                        text: "Sổ Tay Tiền"
                        color: "#F4F5FC"
                        font.pixelSize: 19
                        font.bold: true
                    }
                    Layout.bottomMargin: 20
                }

                // Các nút điều hướng (đã update lại tên file theo project của bồ)
                Button {
                    text: "Trang chủ"
                    Layout.fillWidth: true
                    onClicked: mainStack.replace("qrc:/qml/TrangChuPage.qml")
                }

                Button {
                    text: "Quản lý chi tiêu"
                    Layout.fillWidth: true
                    onClicked: mainStack.replace("qrc:/qml/QuanLyChiTieuPage.qml")
                }

                Button {
                    text: "Thu nhập cá nhân"
                    Layout.fillWidth: true
                    onClicked: mainStack.replace("qrc:/qml/ThuNhapPage.qml")
                }

                Button {
                    text: "Mục tiêu tài chính"
                    Layout.fillWidth: true
                    onClicked: mainStack.replace("qrc:/qml/MucTieuPage.qml")
                }

                // Đẩy các nút lên trên cùng, chừa khoảng trống bên dưới
                Item { Layout.fillHeight: true }

            } // Đóng ColumnLayout
        } // Đóng Sidebar Rectangle

        // ============ MAIN CONTENT ============
        StackView {
            id: mainStack
            Layout.fillWidth: true
            Layout.fillHeight: true

            // Trang mặc định khi vừa mở app lên
            initialItem: "qrc:/qml/TrangChuPage.qml"
        }
    } // Đóng RowLayout
} // Đóng ApplicationWindow