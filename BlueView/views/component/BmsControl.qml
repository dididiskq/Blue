import QtQuick 2.5
import QtQuick.Controls
Page
{
    title: "设备控制"
    property int flagOpen: -1
    background: Rectangle
    {
        // color: "transparent"  // 完全透明
    }


    Rectangle
    {
        id: rectangle
        anchors.top: parent.top
        anchors.topMargin: srcDict.scaled(10)
        width: parent.width
        height: srcDict.scaled(150)
        color: "#E4DDDD"
        Label
        {
            x: 8
            y: 31
            width: 194
            height: 15

            text: "强制充电控制"

        }

        Label {
            id: label
            x: 248
            y: 31
            width: 194
            height: 15
            text: qsTr("强制放电控制")
        }

        Switch
        {
            id: _switch
            x: 8
            y: 71
            text: qsTr("")
            onCheckedChanged:
            {
                if(_switch.checked)
                {
                    print("打开")
                }
                else
                {
                    print("关闭")
                }
            }
        }

        Switch
        {
            id: _switch1
            x: 248
            y: 71
            text: qsTr("")
            onCheckedChanged:
            {
                if(_switch1.checked)
                {
                    print("打开")
                }
                else
                {
                    print("关闭")
                }
            }
        }
    }

    Rectangle
    {
        id: rectangle1
        anchors.top: rectangle.bottom
        anchors.topMargin: srcDict.scaled(30)
        width: parent.width
        height: srcDict.scaled(200)
        // color: "transparent"
        Rectangle
        {
            x: 15
            y: 4
            width: parent.width - 30
            height: 60
            border.color: "red"
            Text {
                id: name
                text: qsTr("系统关机")
            }
        }
        Rectangle
        {
            x: 15
            y: 136
            width: parent.width - 30
            height: 60
            border.color: "red"
            Text {
                id: name1
                text: qsTr("重启系统")
            }
        }
        Rectangle
        {
            x: 15
            y: 70
            width: parent.width - 30
            height: 60
            border.color: "red"
            Text {
                id: name2
                text: qsTr("恢复出厂")
            }
        }
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
                if(flagOpen === 1)
                             {
                                 srcDict.writeToBlue(517, 1)
                                 control.checked = true
                             }
                             else if(flagOpen === 0)
                             {
                                 srcDict.writeToBlue(517, 0)
                                 control.checked = false
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
    Rectangle
    {
        id: rectangle2
        anchors.top: rectangle1.bottom
        anchors.topMargin: srcDict.scaled(30)
        width: parent.width
        height: srcDict.scaled(90)
        color: "#E4DDDD"

        Label
        {
            id: label1
            x: 19
            y: 18
            width: 117
            height: 55
            text: qsTr("弱电开关")
        }

        Switch
        {
            id: control
            x: 310
            y: 31
            text: qsTr("")
            onClicked:
            {
                if(control.checked)
                {
                    passwordDialog.open()
                    flagOpen = 0
                }
                else
                {
                    passwordDialog.open()
                    flagOpen = 1
                }
            }

            // onCheckedChanged:
            // {
            //     if(control.checked)
            //     {
            //         passwordDialog.open()
            //         flagOpen = 1

            //     }
            //     else
            //     {
            //         passwordDialog.open()
            //         flagOpen = 0

            //     }
            // }
            indicator: Rectangle
            {
                implicitWidth: 48
                implicitHeight: 26
                x: control.leftPadding
                y: parent.height / 2 - height / 2

                radius: 13
                color: control.checked ? "green" : "#ffffff"
                border.color: control.checked ? "green" : "#cccccc"

                //小圆点
                Rectangle
                {
                    id : smallRect
                    width: 26
                    height: 26
                    radius: 13
                    color: control.down ? "#cccccc" : "#ffffff"
                    border.color: control.checked ? (control.down ? "#17a81a" : "#21be2b") : "#999999"

                  //改变小圆点的位置
                    NumberAnimation on x
                    {
                        to: smallRect.width
                        running: control.checked ? true : false
                        duration: 200
                    }

                  //改变小圆点的位置
                    NumberAnimation on x
                    {
                        to: 0
                        running: control.checked ? false : true
                        duration: 200
                    }
                }
            }

            //要显示的文本
            // contentItem: Text
            // {
            //     text: control.checked.toString()
            //     font.pixelSize: 50
            //     //鼠标按下时  control.down
            //     color: control.down ? "green" : "red"
            //     verticalAlignment: Text.AlignVCenter
            //     anchors.left: control.indicator.right
            // }
        }
    }
}
