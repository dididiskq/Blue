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
        source: "../res/104.svg"
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
        // anchors.left: parent.left
        anchors.topMargin: srcDict.scaled(150)
        // anchors.leftMargin: srcDict.scaled(45)
        anchors.horizontalCenter: parent.horizontalCenter
        progress: (srcDict.soc === undefined ? 0 : srcDict.soc * 0.01)
        lineWidth: 10
        backgroundColor: "white"
        progressColor: "#34A853"
        textPrefix: getStatus()// 可调整线宽
        z: 1
    }
    Rectangle
    {
        height: 250
        width: parent.width

        anchors.top: parent.top
        anchors.topMargin: srcDict.scaled(130)
        anchors.horizontalCenter: parent.horizontalCenter
        border.color: "red"
        Image
        {

            anchors.fill: parent
            source: "../res/96.svg"
        }
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
        height: parent.height * 0.16
        width: height + 10
        visible: !cameraRect.visible
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: srcDict.scaled(25)
        anchors.topMargin: srcDict.scaled(410)
        Image
        {
            anchors.fill: parent
            source: "../res/102.svg"
        }
        Text
        {
            anchors.centerIn: parent
            font.pixelSize: 20
            color: "white"
            text: String(srcDict.electYa === undefined ? "none" : srcDict.electYa)
        }

        Label
        {
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(25)
                leftMargin: srcDict.scaled(48)
            }
            color: "white"
            text: qsTr("电压")
        }
    }
    // 电流
    Rectangle
    {
        visible: !cameraRect.visible
        color: "transparent"
        height: parent.height * 0.16
        width: height + 10
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: srcDict.scaled(25)
        anchors.topMargin: srcDict.scaled(410)
        Image
        {
            anchors.fill: parent
            source: "../res/103.svg"
        }
        Text
        {
            anchors.centerIn: parent
            font.pixelSize: 20
            color: "white"
            text: String(srcDict.electLiu === undefined ? "none" : srcDict.electLiu)
        }
        Label
        {
            anchors
            {
                top: parent.top
                left: parent.left
                topMargin: srcDict.scaled(25)
                leftMargin: srcDict.scaled(48)
            }
            color: "white"
            text: qsTr("电流")
        }
    }


    Rectangle
    {
        id: param1Rect
        border.color: "red"
        color: "transparent"
        height: 100
        width: parent.width - 20
        anchors.top: parent.top
        anchors.topMargin: 540
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle
        {
            id: warm1
            height: parent.height
            anchors.left: parent.left
            anchors.verticalCenter: param1Rect.verticalCenter
            width: param1Rect.width / 4
            border.color: "red"
            Image
            {
                id: img1
                height: 80
                width: 80
                anchors.horizontalCenter: warm1.horizontalCenter
                source: "../res/warm.svg"
            }
            Label
            {
                anchors.top: img1.bottom
                text: qsTr("电池温度")
                anchors.horizontalCenter: warm1.horizontalCenter
            }
        }
        Rectangle
        {
            id: warm2
            height: parent.height
            anchors.left: warm1.right
            width: param1Rect.width / 4
            border.color: "red"
            Label
            {
                anchors.top: parent.top
                anchors.topMargin: 10
                text: qsTr("T1")
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Label
            {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                text: srcDict.temperature1 === undefined ? "" : srcDict.temperature1
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        Rectangle
        {
            id: warm3
            height: parent.height
            width: param1Rect.width / 4
            anchors.left: warm2.right
            border.color: "red"
            Label
            {
                anchors.top: parent.top
                anchors.topMargin: 10
                text: qsTr("T2")
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Label
            {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                text: srcDict.temperature2 === undefined ? "" : srcDict.temperature2
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        Rectangle
        {
            id: warm4
            height: parent.height
            width: param1Rect.width / 4
            border.color: "red"
            anchors.left: warm3.right
            Label
            {
                anchors.top: parent.top
                anchors.topMargin: 10
                text: qsTr("mos")
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Label
            {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                text: srcDict.mosTemperature === undefined ? "" : srcDict.mosTemperature
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

    }
    Rectangle
    {
        id: param2Rect
        border.color: "red"
        color: "transparent"
        height: 100
        width: parent.width - 20
        anchors.top: param1Rect.bottom
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        Rectangle
        {
            id: bao1
            height: parent.height
            anchors.left: parent.left
            anchors.verticalCenter: param2Rect.verticalCenrter
            width: param2Rect.width / 3
            border.color: "red"
            Image
            {
                id: img
                height: 80
                width: 80
                // anchors.verticalCenter: bao1.verticalCenter
                source: "../res/jingbao.svg"
            }
            Label
            {
                anchors.top: img.bottom
                text: qsTr("异常警报")
            }
            Label
            {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                text: srcDict.alarmlStatus === undefined ? "0" : String(srcDict.alarmlStatus)
            }

        }
        Rectangle
        {
            id: bao2
            height: parent.height
            anchors.left: bao1.right
            width: param2Rect.width / 3
            border.color: "red"
            Image
            {
                id: imgCir
                height: 80
                width: 80
                source: "../res/100.svg"
            }
            Label
            {
                anchors.top: imgCir.bottom
                text: qsTr("循环次数")
            }
            Label
            {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                text: srcDict.cycles_number === undefined ? "0" : srcDict.cycles_number
            }
        }
        Rectangle
        {
            id: bao3
            height: parent.height
            width: param2Rect.width / 3
            anchors.left: bao2.right
            border.color: "red"
            Image
            {
                id: imgYc
                height: 90
                width: 90
                source: "../res/101.svg"
            }
            Label
            {
                anchors.top: imgYc.bottom
                text: qsTr("压差")
            }
            Label
            {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                text: srcDict.yaCha === undefined ? "0" : String(srcDict.yaCha)
            }
        }


    }

    Rectangle
    {
        visible: !cameraRect.visible
        id: rectBlueTiele
        y: 88
        anchors.horizontalCenter: parent.horizontalCenter
        width: srcDict.scaled(270)
        height: srcDict.scaled(47)
        color: "transparent"
        radius: 10
        Label
        {
            id: label6
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
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

}
