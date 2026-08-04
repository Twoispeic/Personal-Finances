import QtQuick 2.15

Item {
    id: root
    property var modelData: [] // Nhận mảng thongKeBieuDo từ C++
    property real lineWidth: 24

    // Tự động yêu cầu vẽ lại Canvas ngay khi mảng modelData thay đổi
    onModelDataChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        antialiasing: true

        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);

            if (!modelData || modelData.length === 0) return;

            var centerX = width / 2;
            var centerY = height / 2;
            var radius = Math.min(centerX, centerY) - (root.lineWidth / 2);

            var startAngle = -Math.PI / 2;

            for (var i = 0; i < modelData.length; i++) {
                var item = modelData[i];

                // Kiểm tra an toàn giá trị phanTram
                if (!item || !item.phanTram || item.phanTram <= 0) continue;

                var sliceAngle = (item.phanTram / 100) * 2 * Math.PI;
                var endAngle = startAngle + sliceAngle;

                ctx.beginPath();
                ctx.arc(centerX, centerY, radius, startAngle, endAngle);
                ctx.lineWidth = root.lineWidth;

                // Nếu item.mau có dữ liệu thì lấy, nếu không sẽ dùng màu mặc định để tránh bị đen
                ctx.strokeStyle = (item.mau && item.mau !== "") ? item.mau : "#35DDC0";
                ctx.stroke();

                startAngle = endAngle;
            }
        }
    }

    Connections {
        target: appController.chiTieu
        function onDuLieuThayDoi() { canvas.requestPaint() }
    }
}