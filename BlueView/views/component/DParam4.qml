import QtQuick 2.5
import QtQuick.Controls
import QtQuick.Layouts
Page
{
    Component.onCompleted:
    {
        srcDict.isShowTool = false
    }
    Button
    {
        height: 50
        width: 130
        text: "< 电流参数"
        x: 0
        y: 0
        font.pixelSize: 20
        onClicked:
        {
            stackView2.pop()
            srcDict.isShowTool = true
        }
        background: Rectangle
        {
            color: "transparent"
        }
    }
    Rectangle
    {
        width: parent.width - 100
        height: 150
        x: 50
        y: 186
        border.color: "red"
        // 参数表格
        GridLayout
        {
            anchors.fill: parent
            columns: 3
            rows: 5
            columnSpacing: 0  // 消除列间距
            rowSpacing: 0    // 消除行间距
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
                Label
                {
                    anchors.centerIn: parent
                    text: "项目"
                }
            }
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
                Label
                {
                    anchors.centerIn: parent
                    text: "参数"
                }
            }
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
                Label
                {
                    anchors.centerIn: parent
                    text: "设定"
                }
            }
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
                Label
                {
                    anchors.centerIn: parent
                    text: "电池串数"
                }
            }
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
            }
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
            }
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
                Label
                {
                    anchors.centerIn: parent
                    text: "电池容量"
                }
            }
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
            }
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
            }
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
            }
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
            }
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
            }
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
            }
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
            }
            Rectangle
            {
                height: parent.height / 5
                width: parent.width / 3
                border.color: "red"
            }

        }
    }
}
