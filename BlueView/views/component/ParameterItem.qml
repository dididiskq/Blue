import QtQuick
import QtQuick.Controls

Row
{
    property string paramName: ""   // 参数名称（如“充电隔热保护”）
    property real paramValue: 0     // 参数值（如60）
    property string paramUnit: "℃"  // 参数单位（如℃）
    property var btnText: "设置"  // 按钮文本
    property alias realValueEditor: valueEditor
    property alias resetTimer: resetTimer

    signal clicked                  // 按钮点击信号

    spacing: 20                     // 行内元素间距

    // 参数名称
    Text {
        width: 150
        text: paramName
        font.pixelSize: 14
        verticalAlignment: Text.AlignVCenter
    }

    // 参数值 + 单位
    Row {
        spacing: 10
        // 可编辑的数值输入框
            TextInput {
                id: valueEditor
                width: 50
                text: paramValue.toString()
                font.pixelSize: 14
                color: activeFocus ? "#0078D4" : "blue"  // 聚焦时显示蓝色边框
                validator: DoubleValidator {           // 限制只能输入数字（含负号和小数）
                    locale: "C"
                    notation: DoubleValidator.StandardNotation
                }
                selectByMouse: true                     // 允许鼠标选择文本
                activeFocusOnPress: true                // 点击时自动聚焦

                // 边框样式
                Rectangle
                {
                    anchors.fill: parent
                    border.color: parent.activeFocus ? "#0078D4" : "transparent"
                    border.width: 1
                    radius: 2
                    z: -1
                }

                // 完成编辑时更新参数值
                onEditingFinished: {
                    paramValue = Number(text)
                    focus = false
                }
            }
        Text
        {
            text: paramUnit
            font.pixelSize: 12
            color: "gray"
        }
    }

    // 设置按钮
    Button
    {
        id: btnReal
        text: btnText
        width: 80
        height: 30
        background: Rectangle
        {
            color: "#0078D4"        // 蓝色按钮
            radius: 4
        }
        contentItem: Text
        {
            text: parent.text
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        onClicked: parent.clicked() // 触发点击信号
    }
    Timer
    {
        id: resetTimer
        interval: 3000
        onTriggered:
        {
            btnText = "设置"
        }
    }
}
