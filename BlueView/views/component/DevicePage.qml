import QtQuick 2.5
import QtQuick.Controls
Page
{

    id: window
    property alias realDrawer: drawer
    background: Rectangle
    {
        color: "#d6e1c2"  // 设置背景颜色
        anchors.fill: parent // 确保填充整个 Page
    }
    header:ToolBar
    {
        height: 50
        ToolButton
        {
            visible: srcDict.isShowTool
            text: stackView.depth > 1 ? "\u25C0" :"\u2630"
            font.pixelSize: 25
            onClicked:
            {
                if(stackView.depth > 1)
                {
                    stackView.pop()
                }
                else
                {
                    drawer.open()
                }
            }
        }

        Label
        {
            text: stackView.currentItem.title
            anchors.centerIn: parent
            font.pixelSize: 25
        }
    }
    Component.onCompleted:
    {
    }

    //侧边抽屉
    Drawer
    {
        id: drawer
        width: window.width * 0.3
        height: window.height
        Column
        {
            anchors.fill: parent

            ItemDelegate
            {
                width: drawer.width
                height: 150
                text: "控制"
                onClicked:
                {
                    stackView.push("DControl.qml")
                    drawer.close()
                }
                Rectangle
                {
                    anchors.fill: parent
                    border.color: "red"
                }
            }
            ItemDelegate
            {
                width: drawer.width
                height: 150
                text: "实时"
                onClicked:
                {
                    // stackView.push("DRealTime.qml")
                    drawer.close()
                }
                Rectangle
                {
                    anchors.fill: parent
                    border.color: "red"
                }
            }
            ItemDelegate
            {
                width: drawer.width
                height: 150
                text: "参数"
                onClicked:
                {
                    stackView.push("DParam.qml")
                    drawer.close()
                }
                Rectangle
                {
                    anchors.fill: parent
                    border.color: "red"
                }
            }
            ItemDelegate
            {
                width: drawer.width
                height: 150
                text: "信息"
                onClicked:
                {
                    stackView.push("DMessage.qml")
                    drawer.close()
                }
                Rectangle
                {
                    anchors.fill: parent
                    border.color: "red"
                }
            }
        }
    }
    StackView
    {
        id: stackView
        anchors.fill: parent

        initialItem: DRealTime{}

    }
}
