import QtQuick 2.15

Item {
    id: root
    property var modelData: [] // Nhận mảng thongKeBieuDo từ C++
    property real lineWidth: 24 // Độ dày của vòng tròn

    Canvas {
        id: canvas
        anchors.fill: parent
        antialiasing: true

        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);

            if (modelData.length === 0) return;

            var centerX = width / 2;
            var centerY = height / 2;
            var radius = Math.min(centerX, centerY) - (root.lineWidth / 2);

            // Xoay góc bắt đầu lên đỉnh (12h)
            var startAngle = -Math.PI / 2;

            for (var i = 0; i < modelData.length; i++) {
                var item = modelData[i];
                if (item.phanTram <= 0) continue;

                // Tính góc cần vẽ cho miếng bánh này
                var sliceAngle = (item.phanTram / 100) * 2 * Math.PI;
                var endAngle = startAngle + sliceAngle;

                ctx.beginPath();
                ctx.arc(centerX, centerY, radius, startAngle, endAngle);
                ctx.lineWidth = root.lineWidth;
                ctx.strokeStyle = item.mau; // Lấy màu từ C++
                ctx.stroke();

                startAngle = endAngle; // Cập nhật góc cho miếng tiếp theo
            }
        }
    }

    // Tự động vẽ lại mỗi khi có người tiêu tiền
    Connections {
        target: appController.chiTieu
        function onDuLieuThayDoi() { canvas.requestPaint() }
    }
}