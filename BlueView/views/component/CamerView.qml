import QtQuick
import QtMultimedia
import QtQuick.Controls
// import QZXing 3.3
Page
{
    property alias capReal: cap
    property var codeData: srcDict.codeData
    visible: true
    anchors.fill: parent
    signal returnPage()

    onCodeDataChanged:
    {
        if(codeData === undefined || codeData === "")
        {
            return;
        }
        returnPage()
    }
    Connections
    {
        target: context
        function onMySignal(message)
        {
            if(message === "1")
            {
                print(codeData + "-已连接")
                myLoader.source = "./component/MainPage.qml"
            }
        }
    }
    Component.onCompleted:
    {
        camera.start()
    }

    Button
    {
        id: button1
        text: "返回"
        onClicked:
        {
            // returnPage()
            myLoader.source = "./component/MainPage.qml"
        }
    }
    CaptureSession
    {
        id: cap
        camera: Camera
        {
            id: camera
            // active: true
        }
        imageCapture: ImageCapture
        {
            id: imgCap
            onImageCaptured: (requestId, img) =>
            {
               // 将捕获的 QImage 传递给 C++ 处理
                srcDict.sendCodeData(img)
               // imageProcessor.processFrame(img)
            }
        }

        videoOutput: output

    }
    VideoOutput
    {
        id: output
        anchors.fill: parent
    }
    Timer
    {
        interval: 1000
        running: cap.camera.active // 摄像头激活时启动
        repeat: true
        onTriggered:
        {
            imgCap.captureToFile("") // 触发捕获
        }
    }


    // 2. 扫描线动画
    Rectangle
    {
        id: scanLine
        width: parent.width
        height: 2
        color: "#00ff00" // 绿色扫描线
        opacity: 0.6     // 半透明效果

        // 初始位置在顶部
        y: 0
        // 线性动画：从上到下循环移动
        NumberAnimation on y {
            from: 0
            to: output.height
            duration: 2000  // 动画时长（毫秒）
            loops: Animation.Infinite // 无限循环
            running: true
        }

        // 添加光影渐变效果（可选）
        // Canvas {
        //        anchors.fill: parent
        //        onPaint: {
        //            var ctx = getContext("2d")
        //            var gradient = ctx.createLinearGradient(0, 0, 0, height)
        //            gradient.addColorStop(0, "transparent")
        //            gradient.addColorStop(0.5, scanLine.color)
        //            gradient.addColorStop(1, "transparent")
        //            ctx.fillStyle = gradient
        //            ctx.fillRect(0, 0, width, height)
        //        }
        //    }
    }

    // 3. 扫描区域边框（可选）
    Rectangle
    {
        anchors.centerIn: parent
        width: 200
        height: 200
        color: "transparent"
        border.color: "#00ff00"
        border.width: 2
    }

}
