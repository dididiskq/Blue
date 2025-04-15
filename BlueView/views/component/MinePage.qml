import QtQuick 2.5

import QtQuick.Controls
import QtQuick.Layouts
Page
{
    id: minePage
    property int currIndex: -1

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
    PasswordDialog
    {
        id: passwordDialog
        x: 50
        y: 200
        title: "安全验证"
        message: "请输入管理员密码"
        onConfirmed: (pwd) =>
        {
            console.log("输入密码:", pwd)
            if(pwd)
            {
                if(currIndex === 3)
                             {
                                 stackViewMine.push("BmsControl.qml")
                             }
                             else if(currIndex === 2)
                             {
                                 stackViewMine.push("OperaBoard.qml")
                             }

                passwordDialog.close()
            }
            else
            {
                passwordDialog.message = "密码错误请重新输入"
            }
        }
        onCanceled: console.log("操作取消")
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
                        currIndex = 2
                        passwordDialog.open()

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
                        // currIndex = 2
                        stackViewMine.push("BmsControl.qml")
                        // passwordDialog.open()

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
