// Main.qml — chỉ đóng vai trò khung + điều hướng
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 1000
    height: 650
    color: "#12172B"
    title: "Quản lý tài chính"

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.preferredWidth: 220
            Layout.fillHeight: true
            color: "#0D111F"

            ColumnLayout {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 16
                spacing: 8   // giảm nếu muốn sát hơn nữa, ví dụ 4

                Button { text: "Trang chủ"; Layout.fillWidth: true; onClicked: stack.currentIndex = 0 }
                Button { text: "Quản lý chi tiêu"; Layout.fillWidth: true; onClicked: stack.currentIndex = 1 }
                Button { text: "Thu nhập cá nhân"; Layout.fillWidth: true; onClicked: stack.currentIndex = 2 }
                Button { text: "Mục tiêu tài chính"; Layout.fillWidth: true; onClicked: stack.currentIndex = 3 }
            }
        }

        // 4 trang — mỗi trang là 1 file .qml riêng, load vào đây
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
}