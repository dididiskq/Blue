import QtQuick 2.5
import QtQuick.Controls

Item
{
    id: pageMain
    // property var blueData: null

    signal hidenTabbar(var type)
    Image
    {
        id: allBg
        width: srcDict.winWidth
        height: srcDict.winHeight
        source: "../res/76.svg"
    }

    Component.onCompleted:
    {
        print("首页加载")
    }
    Component.onDestruction:
    {
        print("首页销毁")
    }
    BatteryArc
    {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: srcDict.scaled(130)
        anchors.leftMargin: srcDict.scaled(45)
        progress: (srcDict.soc === undefined ? 0 : srcDict.soc * 0.01)
        lineWidth: 30
        backgroundColor: "white"
        progressColor: "#34A853"
        textPrefix: getStatus()// 可调整线宽
    }
    function getStatus()
    {
        var res
        if(srcDict.cMos === 1)
        {
            res = qsTr("正在充电")
        }
        else if(srcDict.fMos === 1)
        {
            res = qsTr("正在放电")
        }
        else
        {
            res = qsTr("")
        }

        return res
    }

    Button
    {
        id: buttonSacn
        anchors.left: parent.left
        anchors.leftMargin: srcDict.scaled(25)
        y: 42
        text: qsTr("设备列表")
        width: 80
        height: 40
        onClicked:
        {
            // srcDict.startSearch()
            // blueModel.clear()
            myLoader.source = "./component/BlueList.qml"
        }
        background: Rectangle
        {
            color: "#F0F8FF"
            radius: 10
        }
    }
    Button
    {
        id: buttonCode
        anchors.right: parent.right
        anchors.rightMargin: srcDict.scaled(25)
        y: 42
        width: 80
        height: 40
        text: qsTr("扫一扫")
        onClicked:
        {
            // myLoader.source = "./component/CamerView.qml"
            print("扫码调用")
            hidenTabbar(1)
            cameraRect.visible = true
            cameraRect.capReal.camera.start()
        }
        background: Rectangle
        {
            color: "#F0F8FF"
            radius: 10
        }
    }

    CamerView
    {
        id: cameraRect
        anchors.fill: parent
        visible: false
        onReturnPage:
        {
            hidenTabbar(0)
            cameraRect.visible = false
            capReal.camera.stop()
        }
    }

    // 总电压
    Rectangle
    {
        color: "transparent"
        height: parent.height * 0.15
        width: height
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: srcDict.scaled(25)
        anchors.topMargin: srcDict.scaled(350)
        Image
        {
            anchors.fill: parent
            source: "../res/yaIcon.svg"
        }
        Text
        {
            anchors.centerIn: parent
            font.pixelSize: 20
            color: "blue"
            text: String(srcDict.electYa === undefined ? "" : srcDict.electYa)
        }

        Label
        {
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(20)
                leftMargin: srcDict.scaled(30)
            }
            text: "总电压"
        }
    }
    // 电流
    Rectangle
    {
        color: "transparent"
        height: parent.height * 0.15
        width: height
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: srcDict.scaled(25)
        anchors.topMargin: srcDict.scaled(350)
        Image
        {
            anchors.fill: parent
            source: "../res/liuIcon.svg"
        }
        Text
        {
            anchors.centerIn: parent
            font.pixelSize: 20
            color: "blue"
            text: String(srcDict.electLiu === undefined ? "" : srcDict.electLiu)
        }
        Label
        {
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(20)
                leftMargin: srcDict.scaled(33)
            }

            text: "电流"
        }
    }

    //循环次数
    Rectangle
    {

        height: parent.height * 0.12
        width: parent.width * 0.4
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: srcDict.scaled(25)
        anchors.topMargin: srcDict.scaled(500)
        Image
        {
            height: srcDict.scaled(50)
            width: srcDict.scaled(50)
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(20)
                leftMargin: srcDict.scaled(20)
            }
            source: "../res/cicleIcon.svg"
        }
        Label
        {
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(55)
                leftMargin: srcDict.scaled(80)
            }

            text: "循环次数"
        }
        Text
        {
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(30)
                leftMargin: srcDict.scaled(100)
            }
            text: String(srcDict.cycles_number === undefined ? "" : srcDict.cycles_number)
        }
    }
    //电池温度
    Rectangle
    {

        height: parent.height * 0.12
        width: parent.width * 0.4
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: srcDict.scaled(25)
        anchors.topMargin: srcDict.scaled(500)
        Image
        {
            height: srcDict.scaled(50)
            width: srcDict.scaled(50)
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(20)
                leftMargin: srcDict.scaled(20)
            }
            source: "../res/cellTepmIcon.svg"
        }
        Label
        {
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(55)
                leftMargin: srcDict.scaled(80)
            }

            text: "电池温度"
        }
        Text
        {
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(30)
                leftMargin: srcDict.scaled(100)
            }
            text: srcDict.mosTemperature === undefined ? "" : srcDict.mosTemperature
        }
    }

    //报警
    Rectangle
    {

        height: parent.height * 0.12
        width: parent.width * 0.4
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: srcDict.scaled(25)
        anchors.topMargin: srcDict.scaled(610)
        Image
        {
            height: srcDict.scaled(50)
            width: srcDict.scaled(50)
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(20)
                leftMargin: srcDict.scaled(20)
            }
            source: "../res/alarmIcon.svg"
        }
        Label
        {
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(55)
                leftMargin: srcDict.scaled(80)
            }

            text: "异常报警"
        }
        Text
        {
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(30)
                leftMargin: srcDict.scaled(100)
            }
            text: String(srcDict.alarmlStatus === undefined ? "" : srcDict.alarmlStatus)
        }
    }

    //压差
    Rectangle
    {
        height: parent.height * 0.12
        width: parent.width * 0.4
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: srcDict.scaled(25)
        anchors.topMargin: srcDict.scaled(610)
        Image
        {
            height: srcDict.scaled(50)
            width: srcDict.scaled(50)
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(20)
                leftMargin: srcDict.scaled(20)
            }
            source: "../res/yaChaIcon.svg"
        }
        Label
        {
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(55)
                leftMargin: srcDict.scaled(80)
            }
            text: "电池压差"
        }
        Text
        {
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(30)
                leftMargin: srcDict.scaled(100)
            }
            text: "0"
        }
    }


    //连接蓝牙名称
    Rectangle
    {
        id: rectBlueTiele
        x: 90
        y: 88
        visible: true
        width: srcDict.scaled(270)
        height: srcDict.scaled(47)
        color: "transparent"
        radius: 10
        Label
        {
            id: label6
            x: 70
            y: 16
            font.pixelSize: 14
            anchors.centerIn: parent
            text: srcDict.conectedBlueName
        }
    }

    Timer
    {
        id: mainPageTimer
        interval: 0       // 初始立即触发
        repeat: false     // 首次不重复
        onTriggered:
        {
            if(currIndex != 1)
            {
                return
            }
            // srcDict.sendToBlue(14)
            // srcDict.sendToBlue(4)
            // srcDict.sendToBlue(6)
            // srcDict.sendToBlue(12)
            // srcDict.sendToBlue(18)

            // 调整间隔和重复模式
            interval = 8000
            repeat = true
            start()
        }
    }

    // Rectangle
    // {
    //     id: rectangle1
    //     // visible: !cameraRect.visible
    //     // border.color: "red"
    //     x: 17
    //     y: 328
    //     width: 190
    //     height: 252
    //     color: "#ffffff"
    //     radius: 10

    //     Label
    //     {
    //         id: label
    //         x: 16
    //         y: 54
    //         width: 36
    //         height: 16
    //         text: qsTr("总电量")
    //         font.pixelSize: 17
    //     }
    //     Image
    //     {
    //         x: 18
    //         y: 14
    //         width: 43
    //         height: 43
    //         source: "../res/electR.png"
    //     }

    //     Label
    //     {
    //         id: label2
    //         x: 15
    //         y: 135
    //         text: qsTr("健康度")
    //         font.pixelSize: 17
    //     }
    //     Image
    //     {
    //         x: 18
    //         y: 94
    //         width: 41
    //         height: 41
    //         source: "../res/heath.png"
    //     }
    //     Rectangle
    //     {
    //         id: rectRliang
    //         // visible: !cameraRect.visible
    //         // border.color: "red"
    //         x: 72
    //         y: 15
    //         width: 100
    //         height: 56
    //         color: "#ffffff"

    //         Rectangle
    //         {
    //             id: cellShow
    //             // border.color: "red"
    //             radius: 10
    //             x: 7
    //             y: 11
    //             width: 85
    //             height: 35
    //             color: "#ffffff"
    //             // 动态填充部分
    //                Rectangle {
    //                    id: socFill
    //                    width: parent.width * (srcDict.soc / 100)
    //                    height: parent.height
    //                    radius: parent.radius
    //                    color: {
    //                        if(srcDict.soc <= 20) "#ff4444";    // 红色
    //                        else if(srcDict.soc <= 60) "#ffdd33"; // 黄色
    //                        else "#77dd77" // 绿色
    //                    }
    //                    Behavior on width {
    //                        NumberAnimation { duration: 500 } // 添加动画效果
    //                    }
    //                }

    //                // 显示百分比文本
    //                Text {
    //                    anchors.centerIn: parent
    //                    text: srcDict.soc + "%"
    //                    font.bold: true
    //                    z: 1 // 确保文本在填充层上方
    //                }
    //         }
    //     }
    //     Rectangle
    //     {
    //         id: rectHeath
    //         // visible: !cameraRect.visible
    //         // border.color: "red"
    //         x: 72
    //         y: 95
    //         width: 100
    //         height: 56
    //         color: "#ffffff"
    //         Rectangle
    //         {
    //             id: cellHeathShow
    //             x: 8
    //             y: 11
    //             width: 85
    //             height: 35
    //             color: "#ffffff"
    //             radius: 10
    //             // border.color: "#ff0000"
    //             Rectangle {
    //                     id: sohFill
    //                     width: parent.width * (srcDict.soh / 100)
    //                     height: parent.height
    //                     radius: parent.radius
    //                     color: {
    //                         if(srcDict.soh <= 20) "#ff4444";
    //                         else if(srcDict.soh <= 60) "#ffdd33";
    //                         else "#77dd77"
    //                     }
    //                     Behavior on width {
    //                         NumberAnimation { duration: 500 }
    //                     }
    //                 }

    //                 Text {
    //                     anchors.centerIn: parent
    //                     text: srcDict.soh + "%"
    //                     font.bold: true
    //                     z: 1
    //                 }
    //         }
    //     }
    //     Label {
    //         id: label8
    //         x: 12
    //         y: 215
    //         text: qsTr("电池串数")
    //         font.pixelSize: 17
    //     }

    //     Label {
    //         id: label7
    //         x: 12
    //         y: 174
    //         text: qsTr("电池类型")
    //         font.pixelSize: 17
    //     }

    //     Rectangle {
    //         id: rectangle5
    //         // border.color: "red"
    //         x: 84
    //         y: 170
    //         width: 88
    //         height: 30
    //         color: "#ffffff"
    //         Text
    //         {
    //             anchors.centerIn: parent
    //             id: name2
    //             text: srcDict.celllType === undefined ? "" : srcDict.celllType
    //             // text: "磷酸铁锂"
    //             font.pixelSize: 20
    //             color: "#090045"
    //             font.bold : true
    //         }
    //     }
    //     Rectangle
    //     {
    //         id: rectangle6
    //         // border.color: "red"
    //         x: 84
    //         y: 211
    //         width: 88
    //         height: 30
    //         color: "#ffffff"
    //         Text
    //         {
    //             anchors.centerIn: parent
    //             id: name21
    //             font.pixelSize: 16
    //             text: srcDict.cellNum === undefined ? "" : srcDict.cellNum
    //             // text: "32"
    //             color: "#090045"
    //             font.bold : true
    //         }
    //     }
    // }

    // Rectangle
    // {
    //     id: rectangle2
    //     // visible: !cameraRect.visible
    //     // border.color: "red"
    //     // x: 220
    //     y: 328
    //     anchors.left: parent.left
    //     anchors.leftMargin: srcDict.scaled(0)
    //     width: 190
    //     height: 252
    //     color: "#ffffff"
    //     radius: 10

    //     Label
    //     {
    //         id: label3
    //         x: 29
    //         y: 57
    //         text: qsTr("总电流")
    //         font.pixelSize: 17
    //     }
    //     Rectangle
    //     {
    //         // border.color: "red"
    //         id: rectLiu
    //         x: 86
    //         y: 22
    //         width: 101
    //         height: 45
    //         color: "#ffffff"
    //         Text
    //         {
    //             anchors.centerIn: parent
    //             id: name3
    //             font.pixelSize: 16
    //             // text: "32A"
    //             text: srcDict.electLiu === undefined ? "" : srcDict.electLiu
    //             color: "#090045"
    //             font.bold : true
    //         }
    //     }
    //     Rectangle
    //     {
    //         // border.color: "red"
    //         id: rectYa
    //         x: 86
    //         y: 90
    //         width: 101
    //         height: 45
    //         color: "#ffffff"
    //         Text
    //         {
    //             anchors.centerIn: parent
    //             id: name4
    //             font.pixelSize: 16
    //             // text: "32V"
    //             text: srcDict.electYa === undefined ? "" : srcDict.electYa
    //             color: "#090045"
    //             font.bold : true
    //         }
    //     }
    //     Image
    //     {
    //         x: 34
    //         y: 13
    //         width: 41
    //         height: 41
    //         source: "../res/electL.png"
    //     }
    //     Label
    //     {
    //         id: label1
    //         x: 29
    //         y: 125
    //         text: qsTr("总电压")
    //         font.pixelSize: 17
    //     }
    //     Image
    //     {
    //         x: 34
    //         y: 81
    //         width: 41
    //         height: 41


    //         source: "../res/electY.png"
    //     }
    //     Label
    //     {
    //         id: label4
    //         x: 28
    //         y: 169
    //         text: qsTr("充电MOS")
    //         font.pixelSize: 17
    //     }
    //     Image
    //     {
    //         x: 117
    //         y: 157
    //         width: 42
    //         height: 40
    //         source: srcDict.cMos === undefined ?"../res/guan.png" : (srcDict.cMos === 1 ? "../res/kai.png":"../res/guan.png")
    //         // source: "../res/guan.png"
    //     }

    //     Label
    //     {
    //         id: label5
    //         x: 28
    //         y: 220
    //         text: qsTr("放电MOS")
    //         font.pixelSize: 17
    //     }
    //     Image
    //     {
    //         x: 117
    //         y: 208
    //         width: 42
    //         height: 40
    //         source: srcDict.fMos === undefined ?"../res/guan.png" : (srcDict.fMos === 1 ? "../res/kai.png":"../res/guan.png")
    //         // source: "../res/kai.png"
    //     }
    // }


}
