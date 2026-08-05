// LoginPage.qml — màn hình đăng nhập / đăng ký, dùng chung LoginController đã có sẵn
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    anchors.fill: parent
    color: "#12172B"

    // Phát ra khi đăng nhập/đăng ký thành công, Main.qml lắng nghe để mở khoá giao diện chính
    signal dangNhapThanhCong()

    property bool cheDoDangKy: false

    Rectangle {
        width: 360
        anchors.centerIn: parent
        radius: 16
        color: "#0D111F"
        border.color: "#1B1E42"
        border.width: 1
        implicitHeight: colLayout.implicitHeight + 48

        ColumnLayout {
            id: colLayout
            anchors.fill: parent
            anchors.margins: 24
            spacing: 14

            Text {
                text: cheDoDangKy ? "Tạo tài khoản" : "Đăng nhập"
                color: "#FFFFFF"
                font.pixelSize: 22
                font.bold: true
                Layout.alignment: Qt.AlignHCenter
            }

            TextField {
                id: txtTen
                visible: cheDoDangKy
                Layout.fillWidth: true
                Layout.preferredHeight: visible ? implicitHeight : 0
                placeholderText: "Tên hiển thị"
                color: "#FFFFFF"
                placeholderTextColor: "#5F638F"
                background: Rectangle { color: "#1B1E42"; radius: 8 }
            }

            TextField {
                id: txtTaiKhoan
                Layout.fillWidth: true
                placeholderText: "Tài khoản"
                color: "#FFFFFF"
                placeholderTextColor: "#5F638F"
                background: Rectangle { color: "#1B1E42"; radius: 8 }
            }

            TextField {
                id: txtMatKhau
                Layout.fillWidth: true
                placeholderText: "Mật khẩu"
                echoMode: TextInput.Password
                color: "#FFFFFF"
                placeholderTextColor: "#5F638F"
                background: Rectangle { color: "#1B1E42"; radius: 8 }
                Keys.onReturnPressed: btnXacNhan.clicked()
            }

            Text {
                id: txtLoi
                color: "#FF6B6B"
                text: ""
                visible: text.length > 0
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }

            Button {
                id: btnXacNhan
                Layout.fillWidth: true
                Layout.topMargin: 4
                text: cheDoDangKy ? "Đăng ký" : "Đăng nhập"
                background: Rectangle { color: "#35DDC0"; radius: 8 }
                contentItem: Text {
                    text: btnXacNhan.text
                    color: "#0D111F"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                }
                onClicked: {
                    txtLoi.text = ""
                    if (txtTaiKhoan.text.trim() === "" || txtMatKhau.text === "") {
                        txtLoi.text = "Vui lòng nhập đầy đủ tài khoản và mật khẩu."
                        return
                    }
                    if (cheDoDangKy) {
                        loginController.dangKy(txtTaiKhoan.text, txtMatKhau.text, txtTen.text)
                    } else {
                        loginController.dangNhap(txtTaiKhoan.text, txtMatKhau.text)
                    }
                }
            }

            Text {
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 4
                text: cheDoDangKy ? "Đã có tài khoản? Đăng nhập" : "Chưa có tài khoản? Đăng ký"
                color: "#8A8FC0"
                font.underline: true
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: { cheDoDangKy = !cheDoDangKy; txtLoi.text = "" }
                }
            }
        }
    }

    Connections {
        target: loginController
        function onDangNhapThanhCong(nguoiDungId) {
            appController.datNguoiDungHienTai(nguoiDungId)
            root.dangNhapThanhCong()
        }
        function onDangNhapThatBai(lyDo) {
            txtLoi.text = lyDo
        }
    }
}
