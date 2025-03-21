import QtQuick 2.5
import QtQuick.Controls
import QtQuick.Layouts
Page
{

    Button
    {
        height: 50
        width: 130
        text: "< 快速设置"
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
        x: 0
        y: 264
        width: parent.width
        height: 336


        Button {
            text: "一键铁锂参数"
            width: 120; height: 40
            font.pixelSize: 15
        }
        Button {
            x: 165
            y: 0
            text: "一键三元参数"
            width: 120; height: 40
            font.pixelSize: 15
        }
        Button {
            x: 330
            y: 0
            text: "一键钠离子参数"
            width: 120; height: 40
            font.pixelSize: 15
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
                rows: 3
                columnSpacing: 0  // 消除列间距
                rowSpacing: 0    // 消除行间距
                Rectangle
                {
                    height: parent.height / 3
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
                    height: parent.height / 3
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
                    height: parent.height / 3
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
                    height: parent.height / 3
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
                    height: parent.height / 3
                    width: parent.width / 3
                    border.color: "red"
                }
                Rectangle
                {
                    height: parent.height / 3
                    width: parent.width / 3
                    border.color: "red"
                }
                Rectangle
                {
                    height: parent.height / 3
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
                    height: parent.height / 3
                    width: parent.width / 3
                    border.color: "red"
                }
                Rectangle
                {
                    height: parent.height / 3
                    width: parent.width / 3
                    border.color: "red"
                }

            }
        }
    }


    Component.onCompleted:
    {
        srcDict.isShowTool = false
    }
}
