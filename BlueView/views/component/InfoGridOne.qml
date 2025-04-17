import QtQuick
import QtQuick.Controls

Row
{
    width: parent.width
    spacing: 10

    Rectangle
    {
        width: parent.width / 2 - 5
        height: srcDict.scaled(130)
        color: "transparent"

        Rectangle
        {
            height: 50
            width: 130 * (srcDict.soc / 100)
            border.color: "red"
            radius: 10
            anchors.horizontalCenter: parent.horizontalCenter
            color: {
                if(srcDict.soc <= 20) "#ff4444";    // 红色
                else if(srcDict.soc <= 60) "#ffdd33"; // 黄色
                else "#77dd77" // 绿色
            }
            Behavior on width {
                NumberAnimation { duration: 500 } // 添加动画效果
            }
        }

        Column
        {
            spacing: 10
            anchors
            {
                top: parent.top
                topMargin: srcDict.scaled(55)
                // verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }
            Label
            {
                text: "SOC：" + String(srcDict.soc === undefined ? "none" : srcDict.soc)
                font.pixelSize: 14
                color: "#666666"
            }
            Label
            {
                text: "总容量：" + String(srcDict.fcc === undefined ? "none" : srcDict.fcc)
                font.pixelSize: 14
                color: "#666666"
            }
            Label
            {
                text: "剩余容量：" + String(srcDict.remaining_capacity === undefined ? "none" : srcDict.remaining_capacity)
                font.pixelSize: 14
                color: "#666666"
            }
        }
    }

    Rectangle
    {
        width: parent.width / 2 - 5
        height: srcDict.scaled(130)
        color: "transparent"

        // 参数名称
        Column
        {
            spacing: 20
            anchors
            {
                left: parent.left
                leftMargin: srcDict.scaled(50)
                verticalCenter: parent.verticalCenter
            }
            Label
            {
                text: "充电MOS"
                font.pixelSize: 14
                color: "#666666"
            }
            Label
            {
                text: "放电MOS"
                font.pixelSize: 14
                color: "#666666"
            }
            Label
            {
                text: "均衡状态"
                font.pixelSize: 14
                color: "#666666"
            }
        }
        Column
        {
            spacing: 20
            anchors
            {
                right: parent.right
                rightMargin: srcDict.scaled(50)
                verticalCenter: parent.verticalCenter
            }
            Image
            {
                height: 20
                width: 20
                source: srcDict.cMos === undefined ? "../res/guan.png" : (srcDict.cMos === 1 ? "../res/kai.png" : "../res/guan.png")
            }
            Image
            {
                height: 20
                width: 20
                source: srcDict.fMos === undefined ? "../res/guan.png" : (srcDict.fMos === 1 ? "../res/kai.png" : "../res/guan.png")
            }
            Image
            {
                height: 20
                width: 20
                source: srcDict.junhengStatus === undefined ? "../res/guan.png" : (srcDict.junhengStatus === 1 ? "../res/kai.png" : "../res/guan.png")
            }
        }

    }
}
