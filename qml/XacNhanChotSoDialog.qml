import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Dialog {
    id: root
    title: "Chốt sổ tháng này?"
    modal: true
    standardButtons: Dialog.Yes | Dialog.No
    width: 380

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    ColumnLayout {
        anchors.fill: parent
        spacing: 12

        Text {
            text: "Sau khi chốt sổ, số tiền dư của tháng sẽ được phân bổ vào các mục tiêu dài hạn. Hành động này không thể hoàn tác."
            color: "#8A8FC0"
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }
    }

    onAccepted: {
        // ketThucThang() giờ tự lo luôn việc chuyển sang tháng mới + refresh toàn bộ,
        // không cần gọi thêm appController.quaThangMoi() nữa.
        var conDu = appController.ketThucThang();
        console.log("Con du sau khi chot so:", conDu);
    }
}