import QtQuick 2.5
import QtQuick.Controls
import Qt5Compat.GraphicalEffects // 需要导入图形效果模块
Page
{

    id: window
    property alias realDrawer: drawer
    property var realTimer: mainPageTimer
    Timer
    {
        id: mainPageTimer
        interval: 0       // 初始立即触发
        repeat: false     // 首次不重复
        onTriggered:
        {

            srcDict.getProtectMessage(1)
            // 调整间隔和重复模式
            interval = 5000
            repeat = true
            start()
        }
    }

    background: Rectangle
    {
        color: "transparent"  // 完全透明
    }
    header:ToolBar
    {
        id: headTool
        height: srcDict.scaled(80)
        background: Rectangle
        {
            anchors.fill: parent
            color: "#318be4"
        }
        ToolButton
        {
            // visible: srcDict.isShowTool
            anchors.left: parent.left
            anchors.bottom: parent.bottom
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
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 25
        }
    }
    Component.onCompleted:
    {
    }
    StackView
    {
        id: stackView
        anchors.fill: parent

        initialItem: DRealTime{}
        // 添加模糊层
        layer.enabled: drawer.position > 0 // 抽屉展开时启用效果
        layer.effect: FastBlur
        {
            radius: 32 // 模糊半径（0-64）
            transparentBorder: true // 允许边缘透明
            Behavior on radius { // 添加过渡动画
                NumberAnimation { duration: 200 }
            }
        }
    }
    //侧边抽屉
    Drawer
    {
        id: drawer
        width: window.width * 0.7
        height: window.height * 0.8
        y: headTool.height
        dim: false // 关闭默认的暗色遮罩
        edge: Qt.LeftEdge
        // 添加半透明背景
        background: Rectangle
        {
            color: "#80000000" // 半透明黑色
            Rectangle
            { // 侧边栏内容背景
                width: parent.width
                height: parent.height
                color: "#318be4"
                radius: 10
                anchors.right: parent.right
            }
        }

        Column
        {
            anchors.fill: parent

            ItemDelegate
            {
                width: drawer.width
                height: 50
                text: "快速设置"
                onClicked:
                {
                    stackView.push("DParam1.qml")
                    drawer.close()
                }
                Rectangle
                {
                    anchors.fill: parent
                    border.color: "red"
                    radius: 10
                }
            }
            ItemDelegate
            {
                width: drawer.width
                height: 50
                text: "电压参数"
                onClicked:
                {
                    stackView.push("DParam2.qml")
                    drawer.close()
                }
                Rectangle
                {
                    anchors.fill: parent
                    border.color: "red"
                    radius: 10
                }
            }
            ItemDelegate
            {
                width: drawer.width
                height: 50
                text: "温度参数"
                onClicked:
                {
                    stackView.push("DParam3.qml")
                    drawer.close()
                }
                Rectangle
                {
                    anchors.fill: parent
                    border.color: "red"
                    radius: 10
                }
            }
            ItemDelegate
            {
                width: drawer.width
                height: 50
                text: "电流参数"
                onClicked:
                {
                    stackView.push("DParam4.qml")
                    drawer.close()
                }
                Rectangle
                {
                    anchors.fill: parent
                    border.color: "red"
                    radius: 10
                }
            }
            ItemDelegate
            {
                width: drawer.width
                height: 50
                text: "均衡参数"
                onClicked:
                {
                    stackView.push("DParam5.qml")
                    drawer.close()
                }
                Rectangle
                {
                    anchors.fill: parent
                    border.color: "red"
                    radius: 10
                }
            }
            ItemDelegate
            {
                width: drawer.width
                height: 50
                text: "系统参数"
                onClicked:
                {
                    stackView.push("DParam6.qml")
                    drawer.close()
                }
                Rectangle
                {
                    anchors.fill: parent
                    border.color: "red"
                    radius: 10
                }
            }
        }
    }

}
