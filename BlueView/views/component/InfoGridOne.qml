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

        Image
        {
            height: 50
            width: 130
            source: "../res/cellDev.png"
            anchors
            {
                top: parent.top
                // topMargin: srcDict.scaled(10)
                // verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
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
                text: "SOC" + srcDict.soc === undefined ? "" : String(srcDict.soc)
                font.pixelSize: 14
                color: "#666666"
            }
            Label
            {
                text: "总容量" + srcDict.fcc === undefined ? "" : String(srcDict.fcc)
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
                source: "../res/guan.png"
            }
        }

    }
}
