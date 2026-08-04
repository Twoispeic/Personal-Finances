import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Item {
    anchors.fill: parent
    anchors.margins: 40

    ColumnLayout {
        anchors.fill: parent
        spacing: 28

        // ================= 1. TOPBAR =================
        RowLayout {
            Layout.fillWidth: true
            ColumnLayout {
                spacing: 4
                Text {
                    text: "Thu nhập cá nhân"
                    color: "#F4F5FC"
                    font.pixelSize: 26
                    font.bold: true
                }
                Text {
                    text: "Theo dõi dòng tiền vào và tích lũy trong 12 tháng qua"
                    color: "#8A8FC0"
                    font.pixelSize: 14
                }
            }
            Item { Layout.fillWidth: true } // Đẩy Topbar ra góc
        }

        // ================= 2. KHU VỰC NHẬP & THỐNG KÊ =================
        RowLayout {
            Layout.fillWidth: true
            height: 120
            spacing: 18

            // Ô nhập thu nhập
            Rectangle {
                Layout.preferredWidth: 350
                Layout.fillHeight: true
                color: "#1B1E42"
                radius: 18
                border.color: "#12FFFFFF"

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 12

                    Text { text: "THÊM THU NHẬP THÁNG NÀY"; color: "#8A8FC0"; font.pixelSize: 12; font.bold: true }

                    RowLayout {
                        TextField {
                            id: inputThuNhap
                            Layout.fillWidth: true
                            placeholderText: "Nhập số tiền..."
                            color: "#F4F5FC"
                            font.pixelSize: 16
                            background: Rectangle { color: "#212553"; radius: 8 }
                            // Chỉ cho phép nhập số
                            validator: RegularExpressionValidator { regularExpression: /^[0-9]+$/ }
                        }

                        Button {
                            text: "Lưu"
                            background: Rectangle { color: "#6E7BFA"; radius: 8 }
                            contentItem: Text {
                                text: parent.text; color: "#FFF"; font.bold: true
                                horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                            }
                            onClicked: {
                                if(inputThuNhap.text !== "") {
                                    // Gọi C++ lưu data
                                    appController.thuNhap.luuThang(parseFloat(inputThuNhap.text))
                                    inputThuNhap.text = "" // Xóa form sau khi lưu
                                }
                            }
                        }
                        Button {
                                text: "Xóa"
                                background: Rectangle { color: "#F2508C"; radius: 8 }
                                contentItem: Text {
                                    text: parent.text; color: "#FFF"; font.bold: true
                                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                                }
                                onClicked: appController.thuNhap.xoaThangHienTai()
                            }
                    }
                }
            }

            // Thẻ: Tổng thu nhập 12 tháng
            Rectangle {
                Layout.fillWidth: true; Layout.fillHeight: true
                color: "#1B1E42"; radius: 18; border.color: "#12FFFFFF"
                ColumnLayout {
                    anchors.fill: parent; anchors.margins: 20; spacing: 8
                    Text { text: "TỔNG THU NHẬP (12 THÁNG)"; color: "#8A8FC0"; font.pixelSize: 12; font.bold: true }
                    Text {
                        text: appController.thuNhap.tongThuNhap12Thang.toLocaleString('vi-VN') + " đ"
                        color: "#35DDC0"; font.pixelSize: 26; font.bold: true
                    }
                }
            }

            // Thẻ: Tổng tiền tiết kiệm
            Rectangle {
                Layout.fillWidth: true; Layout.fillHeight: true
                color: "#1B1E42"; radius: 18; border.color: "#12FFFFFF"
                ColumnLayout {
                    anchors.fill: parent; anchors.margins: 20; spacing: 8
                    Text { text: "HŨ TIẾT KIỆM KHẢ DỤNG"; color: "#8A8FC0"; font.pixelSize: 12; font.bold: true }
                    Text {
                        text: appController.huTietKiem.toLocaleString('vi-VN') + " đ"
                        color: "#FFB35C"; font.pixelSize: 26; font.bold: true
                    }
                }
            }
        }

        // ================= 3. BIỂU ĐỒ CỘT =================
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 280
                    color: "#1B1E42"
                    radius: 20
                    border.color: "#12FFFFFF"

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 24
                        spacing: 15

                        Text {
                            text: "Biểu đồ thu nhập 12 tháng gần nhất"
                            color: "#F4F5FC"
                            font.pixelSize: 16
                            font.bold: true
                        }

                        // Vẽ các cột bar chart dùng Row thay vì RowLayout để kiểm soát tốt hơn
                        Row {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            spacing: 20
                            leftPadding: 10

                            Repeater {
                                model: appController.thuNhap.thongKe12Thang

                                delegate: Item {
                                    width: 65
                                    height: parent.height

                                    function getMaxTien() {
                                        let max = 0;
                                        let dataList = appController.thuNhap.thongKe12Thang;
                                        for(let i = 0; i < dataList.length; i++) {
                                            if(dataList[i].soTien > max) max = dataList[i].soTien;
                                        }
                                        return max === 0 ? 1 : max;
                                    }

                                    // Thanh biểu đồ cột
                                    Rectangle {
                                        width: 32
                                        height: (modelData.soTien / getMaxTien()) * 140
                                        anchors.bottom: txtThang.top
                                        anchors.bottomMargin: 12
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        color: modelData.soTien > 0 ? "#6E7BFA" : "#12FFFFFF"
                                        radius: 6
                                    }

                                    // Tên tháng dưới đáy
                                    Text {
                                        id: txtThang
                                        text: modelData.thang
                                        color: "#5F638F"
                                        font.pixelSize: 12
                                        font.bold: true
                                        anchors.bottom: parent.bottom
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }
                                }
                            }
                        }
                    }
                }
            }
}