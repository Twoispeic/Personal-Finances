import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Dialog {
    id: root
    width: 400
    modal: true

    // Căn giữa màn hình (Vì Dialog không xài anchors.centerIn được)
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    // Bỏ tiêu đề mặc định và các nút chuẩn để tự vẽ cho đẹp
    title: ""
    standardButtons: Dialog.NoButton

    // Nền bo góc xịn xò
    background: Rectangle {
        color: "#1B1E42"
        radius: 20
        border.color: "#12FFFFFF"
    }

    contentItem: ColumnLayout {
        spacing: 20

        // Tiêu đề tự vẽ
        Text {
            text: "Thêm chi tiêu"
            color: "#F4F5FC"
            font.pixelSize: 18
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 10
        }

        // ================= 1. Ô CHỌN LOẠI CHI TIÊU =================
        ColumnLayout {
            spacing: 8
            Layout.fillWidth: true
            Text {
                text: "Loại chi tiêu:"
                color: "#35DDC0"
                font.pixelSize: 14
                font.bold: true
            }

            ComboBox {
                id: comboLoai
                Layout.fillWidth: true
                // Bồ có thể sửa danh sách này cho khớp với app của bồ nha
                model: ["Tiền sinh hoạt", "Tiền điện nước", "Tiền nhà", "Khác"]
            }
        }

        // ================= 2. Ô NHẬP SỐ TIỀN =================
        ColumnLayout {
            spacing: 8
            Layout.fillWidth: true
            Text {
                text: "Số tiền:"
                color: "#35DDC0"
                font.pixelSize: 14
                font.bold: true
            }

            SpinBox {
                id: spinTien
                from: 0
                to: 999999999
                editable: true
                Layout.fillWidth: true
            }
        }

        // ================= 3. HÀNG NÚT HỦY / THÊM =================
        RowLayout {
            Layout.fillWidth: true
            Layout.topMargin: 10
            spacing: 16

            // Nút Hủy
            Rectangle {
                Layout.fillWidth: true
                height: 40
                radius: 10
                color: "#26F2508C" // Hồng nhạt cho Cancel
                Text { anchors.centerIn: parent; text: "Hủy"; color: "#F2508C"; font.bold: true }
                MouseArea {
                    anchors.fill: parent; cursorShape: Qt.PointingHandCursor;
                    onClicked: root.reject()
                }
            }

            // Nút Thêm
            Rectangle {
                Layout.fillWidth: true
                height: 40
                radius: 10
                color: "#35DDC0" // Xanh ngọc cho OK
                Text { anchors.centerIn: parent; text: "Thêm"; color: "#0D111F"; font.bold: true }
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        // Gọi hàm C++ để lưu dữ liệu.
                        // Bồ nhớ kiểm tra lại tên hàm themChiTieu bên C++ cho chuẩn xác nha!
                        appController.chiTieu.themChiTieu(comboLoai.currentText, spinTien.value)

                        root.accept() // Đóng popup
                    }
                }
            }
        }
    }
}