import QtQuick 2.5
import QtQuick.Controls

Page
{
    id: pageMain
    // property var blueData: null
    property var blueData: srcDict.blueDataReal
    signal hidenTabbar(var type)
    property string conectedName: ""
    property bool isOn: false

    // background: Rectangle
    // {
    //     // color: "#d6e1c2"  // 设置背景颜色
    //     anchors.fill: parent // 确保填充整个 Page

    // }
    Image
    {
        width: srcDict.winWidth
        height: srcDict.winHeight
        // anchors.fill: parent
        id: name
        source: "../res/64.svg"
    }

    Component.onCompleted:
    {
        print("首页加载")
    }
    Component.onDestruction:
    {
        print("首页销毁")
    }

    Button
    {
        id: buttonSacn
        x: 33
        y: 42
        text: qsTr("扫描蓝牙")
        width: 80
        height: 40
        onClicked:
        {
            srcDict.startSearch()
            blueModel.clear()
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
        x: 325
        y: 42
        width: 80
        height: 40
        text: qsTr("扫一扫")
        onClicked:
        {
            myLoader.source = "./component/CamerView.qml"
            print("扫码调用")
            // hidenTabbar(1)
            // cameraRect.visible = true
            // cameraRect.capReal.camera.start()
        }
        background: Rectangle
        {
            color: "#F0F8FF"
            radius: 10
        }
    }
    Button
    {
        height: 50
        width: 50

        text: "test"
        onClicked:
        {
            isOn = !isOn
        }
    }

    // CamerView
    // {
    //     id: cameraRect
    //     anchors.fill: parent
    //     onReturnPage:
    //     {
    //         hidenTabbar(0)
    //         cameraRect.visible = false
    //         capReal.camera.stop()
    //     }
    // }

    function simulateBotReply(data)
    {
         // console.log("Received data:", JSON.stringify(data))
        blueModel.append({text: data.name, addr: data.address})
    }
    // 数据模型，存储对话内容
    ListModel
    {
        id: blueModel
    }

    Rectangle
    {
        id: cellRect
        // color: "red"
        x: 25
        y: 159
        z : isOn === true ? 1 : 0
        height: 300
        radius: 10
        width: 400
        Image
        {
            height: 250
            width: 250
            source: "../res/test.svg"
        }
    }

    Rectangle
    {
        id: mainRect
        x: 25
        y: 159
        z : isOn === false ? 1 : 0
        height: 300
        // border.color: "#db3a3a"
        radius: 10
        color: "#f2f8ed"
        width: 400
        // visible: !cameraRect.visible
        // 使用 Flickable 替代 ListView
        Flickable
        {
            id: blueFlickable
            width: parent.width
            height: parent.height
            clip: true // 确保内容在边界内剪裁
            contentWidth: blueColumn.width
            contentHeight: blueColumn.height

            Column
            {
                id: blueColumn
                width: blueFlickable.width
                spacing: 10

                // 每条消息的显示方式
                Repeater
                {
                    model: blueModel
                    delegate: Rectangle
                    {
                        id: deRect
                        width: messageText.implicitWidth + 20
                        height: messageText.implicitHeight + 40
                        color: "white"
                        border.color: "#C1FFC1"
                        radius: 10
                        Text
                        {
                            id: messageText
                            color:  "black"
                            anchors.centerIn: parent
                            width: parent.width
                            wrapMode: Text.Wrap
                            text: model.text
                            horizontalAlignment: Text.AlignHCenter // 关键修改：水平居中
                            font.pixelSize: 28
                        }
                        MouseArea
                        {
                            anchors.fill: parent
                            onClicked:
                            {
                                print("发送连接请求",model.text ,model.addr)
                                label6.text = model.text + "-正在连接"
                                rectBlueTiele.visible = true
                                deRect.color = "green"
                                srcDict.connectBlue(model.addr)
                                conectedName = model.text
                            }
                            onPressed:
                            {
                            }
                            onReleased:
                            {
                                releaseTimer.start()
                            }
                            Timer
                            {
                                id: releaseTimer
                                interval: 250
                                repeat: false
                                onTriggered:
                                {
                                    deRect.color = "white"
                                }
                            }
                        }
                    }
                }
            }
            // 自动滚动到底部
            onContentHeightChanged:
            {
                // blueFlickable.contentY = blueColumn.height - blueFlickable.height
            }
        }
    }

    Rectangle
    {
        id: rectBlueTiele
        x: 90
        y: 88
        visible: false
        width: 270
        height: 47
        color: "#C1FFC1"
        radius: 10
        Label
        {
            id: label6
            x: 70
            y: 16
            font.pixelSize: 14
            anchors.centerIn: parent
            text: qsTr("")
        }
    }
    Connections
    {
        target: context
        function onMySignal(message)
        {
            if(message === "1")
            {
                label6.text = conectedName + "-已连接"
            }
            else if(message === "2")
            {
                mainPageTimer.start();
            }
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
            srcDict.sendToBlue(14)
            srcDict.sendToBlue(4)
            srcDict.sendToBlue(6)
            srcDict.sendToBlue(12)
            srcDict.sendToBlue(18)

            // 调整间隔和重复模式
            interval = 8000
            repeat = true
            start()
        }
    }

    Rectangle
    {
        id: rectangle1
        // visible: !cameraRect.visible
        // border.color: "red"
        x: 25
        y: 497
        width: 190
        height: 252
        color: "#ffffff"
        radius: 10

        Label
        {
            id: label
            x: 16
            y: 54
            width: 36
            height: 16
            text: qsTr("总电量")
            font.pixelSize: 17
        }
        Image
        {
            x: 18
            y: 14
            width: 43
            height: 43
            source: "../res/electR.png"
        }

        Label
        {
            id: label2
            x: 15
            y: 135
            text: qsTr("健康度")
            font.pixelSize: 17
        }
        Image
        {
            x: 18
            y: 94
            width: 41
            height: 41
            source: "../res/heath.png"
        }
        Rectangle
        {
            id: rectRliang
            // visible: !cameraRect.visible
            // border.color: "red"
            x: 72
            y: 15
            width: 100
            height: 56
            color: "#ffffff"

            Rectangle
            {
                id: cellShow
                // border.color: "red"
                radius: 10
                x: 7
                y: 11
                width: 85
                height: 35
                color: "#ffffff"
                // 动态填充部分
                   Rectangle {
                       id: socFill
                       width: parent.width * (srcDict.soc / 100)
                       height: parent.height
                       radius: parent.radius
                       color: {
                           if(srcDict.soc <= 20) "#ff4444";    // 红色
                           else if(srcDict.soc <= 60) "#ffdd33"; // 黄色
                           else "#77dd77" // 绿色
                       }
                       Behavior on width {
                           NumberAnimation { duration: 500 } // 添加动画效果
                       }
                   }

                   // 显示百分比文本
                   Text {
                       anchors.centerIn: parent
                       text: srcDict.soc + "%"
                       font.bold: true
                       z: 1 // 确保文本在填充层上方
                   }
            }
        }
        Rectangle
        {
            id: rectHeath
            // visible: !cameraRect.visible
            // border.color: "red"
            x: 72
            y: 95
            width: 100
            height: 56
            color: "#ffffff"
            Rectangle
            {
                id: cellHeathShow
                x: 8
                y: 11
                width: 85
                height: 35
                color: "#ffffff"
                radius: 10
                // border.color: "#ff0000"
                Rectangle {
                        id: sohFill
                        width: parent.width * (srcDict.soh / 100)
                        height: parent.height
                        radius: parent.radius
                        color: {
                            if(srcDict.soh <= 20) "#ff4444";
                            else if(srcDict.soh <= 60) "#ffdd33";
                            else "#77dd77"
                        }
                        Behavior on width {
                            NumberAnimation { duration: 500 }
                        }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: srcDict.soh + "%"
                        font.bold: true
                        z: 1
                    }
            }
        }
        Label {
            id: label8
            x: 12
            y: 215
            text: qsTr("电池串数")
            font.pixelSize: 17
        }

        Label {
            id: label7
            x: 12
            y: 174
            text: qsTr("电池类型")
            font.pixelSize: 17
        }

        Rectangle {
            id: rectangle5
            // border.color: "red"
            x: 84
            y: 170
            width: 88
            height: 30
            color: "#ffffff"
            Text
            {
                anchors.centerIn: parent
                id: name2
                text: srcDict.celllType === undefined ? "" : srcDict.celllType
                // text: "磷酸铁锂"
                font.pixelSize: 20
                color: "#090045"
                font.bold : true
            }
        }
        Rectangle
        {
            id: rectangle6
            // border.color: "red"
            x: 84
            y: 211
            width: 88
            height: 30
            color: "#ffffff"
            Text
            {
                anchors.centerIn: parent
                id: name21
                font.pixelSize: 16
                text: srcDict.cellNum === undefined ? "" : srcDict.cellNum
                // text: "32"
                color: "#090045"
                font.bold : true
            }
        }
    }

    Rectangle
    {
        id: rectangle2
        // visible: !cameraRect.visible
        // border.color: "red"
        x: 235
        y: 497
        width: 190
        height: 252
        color: "#ffffff"
        radius: 10

        Label
        {
            id: label3
            x: 29
            y: 57
            text: qsTr("总电流")
            font.pixelSize: 17
        }
        Rectangle
        {
            // border.color: "red"
            id: rectLiu
            x: 86
            y: 22
            width: 101
            height: 45
            color: "#ffffff"
            Text
            {
                anchors.centerIn: parent
                id: name3
                font.pixelSize: 16
                // text: "32A"
                text: srcDict.electLiu === undefined ? "" : srcDict.electLiu
                color: "#090045"
                font.bold : true
            }
        }
        Rectangle
        {
            // border.color: "red"
            id: rectYa
            x: 86
            y: 90
            width: 101
            height: 45
            color: "#ffffff"
            Text
            {
                anchors.centerIn: parent
                id: name4
                font.pixelSize: 16
                // text: "32V"
                text: srcDict.electYa === undefined ? "" : srcDict.electYa
                color: "#090045"
                font.bold : true
            }
        }
        Image
        {
            x: 34
            y: 13
            width: 41
            height: 41
            source: "../res/electL.png"
        }
        Label
        {
            id: label1
            x: 29
            y: 125
            text: qsTr("总电压")
            font.pixelSize: 17
        }
        Image
        {
            x: 34
            y: 81
            width: 41
            height: 41


            source: "../res/electY.png"
        }
        Label
        {
            id: label4
            x: 28
            y: 169
            text: qsTr("充电MOS")
            font.pixelSize: 17
        }
        Image
        {
            x: 117
            y: 157
            width: 42
            height: 40
            source: srcDict.cMos === undefined ?"../res/guan.png" : (srcDict.cMos === 1 ? "../res/kai.png":"../res/guan.png")
            // source: "../res/guan.png"
        }

        Label
        {
            id: label5
            x: 28
            y: 220
            text: qsTr("放电MOS")
            font.pixelSize: 17
        }
        Image
        {
            x: 117
            y: 208
            width: 42
            height: 40
            source: srcDict.fMos === undefined ?"../res/guan.png" : (srcDict.fMos === 1 ? "../res/kai.png":"../res/guan.png")
            // source: "../res/kai.png"
        }
    }

    onBlueDataChanged:
    {
        if(blueData === undefined)
        {
            return
        }
        simulateBotReply(blueData)
    }
}
