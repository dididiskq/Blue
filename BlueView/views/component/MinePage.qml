import QtQuick 2.5

import QtQuick.Controls
import QtQuick.Layouts
Page
{
    id: minePage


    header:ToolBar
    {
        height: srcDict.scaled(50)
        background: Rectangle
        {
            anchors.fill: parent
            color: "#318be4"
        }
        ToolButton
        {
            text: stackViewMine.depth > 1 ? "\u25C0" :""
            font.pixelSize: 25
            onClicked:
            {
                if(stackViewMine.depth > 1)
                {
                    stackViewMine.pop()
                }
                else
                {
                    drawer.open()
                }
            }
        }

        Label
        {
            text: stackViewMine.currentItem.title
            anchors.centerIn: parent
            font.pixelSize: 25
        }
    }
    StackView
    {
        id: stackViewMine
        anchors.fill: parent
        initialItem: mainMenu
    }
    Page
    {
        id: mainMenu
        title: ""
        background: Rectangle
        {
            id: rectBg
            color: "white"
            // color: "transparent"  // 完全透明
            // color: "#80000000"//半透明
        }
        Column
        {
            spacing: srcDict.scaled(20)
            anchors.top: parent.top
            // anchors.topMargin: srcDict.scaled(50)
            width: minePage.width

            Rectangle
            {
                height: srcDict.scaled(60)
                width: srcDict.scaled(380)
                Layout.alignment: Qt.AlignHCenter // 关键代码
                radius: 10
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        stackViewMine.push("CellMessage.qml")
                    }
                }

                Label
                {
                    text: "电池信息"
                    font.pixelSize: 30
                    anchors.centerIn: parent
                }
                Image
                {
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    height: parent.height
                    width: srcDict.scaled(60)
                    source: "../res/mineComeIn.svg"
                }
            }

            Rectangle
            {
                height: srcDict.scaled(60)
                width: srcDict.scaled(380)
                radius: 10
                Layout.alignment: Qt.AlignHCenter // 关键代码
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                    }
                }

                Label
                {
                    text: "固件升级"
                    font.pixelSize: 30
                    anchors.centerIn: parent
                }
                Image
                {
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    height: parent.height
                    width: srcDict.scaled(60)
                    source: "../res/mineComeIn.svg"
                }
            }
            Rectangle
            {
                height: srcDict.scaled(60)
                width: srcDict.scaled(380)
                Layout.alignment: Qt.AlignHCenter // 关键代码
                radius: 10
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        stackViewMine.push("OperaBoard.qml")
                    }
                }

                Label
                {
                    text: "进入生产操作面板"
                    font.pixelSize: 30
                    anchors.centerIn: parent
                }
                Image
                {
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    height: parent.height
                    width: srcDict.scaled(60)
                    source: "../res/mineComeIn.svg"
                }
            }
            Rectangle
            {
                height: srcDict.scaled(60)
                width: srcDict.scaled(380)
                Layout.alignment: Qt.AlignHCenter // 关键代码
                radius: 10
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        stackViewMine.push("BmsControl.qml")
                    }
                }

                Label
                {
                    text: "BMS控制"
                    font.pixelSize: 30
                    anchors.centerIn: parent
                }
                Image
                {
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    height: parent.height
                    width: srcDict.scaled(60)
                    source: "../res/mineComeIn.svg"
                }
            }
        }
    }
}
