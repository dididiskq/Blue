import QtQuick
import QtQuick.Shapes

Item {
    id: root
    width: 300
    height: 300

    // 可配置属性
    property real progress: 0.8    // 进度值（0-1）
    property int lineWidth: 20     // 进度条粗细
    property color progressColor: "white"  // 进度条颜色
    property color pointerColor: "#FF0000" // 指针颜色

    // 进度动画
    Behavior on progress {
        NumberAnimation {
            duration: 500
            easing.type: Easing.OutCubic
        }
    }

    // 进度圆环（动态部分）
    Shape
    {
        anchors.fill: parent
        antialiasing: true
        ShapePath {
            strokeWidth: root.lineWidth - 5
            strokeColor: root.progressColor
            capStyle: ShapePath.RoundCap
            fillColor: "transparent"
            startX: root.width/2 + root.width/2 * Math.cos(180 * Math.PI/180)
            startY: root.height/2 + root.height/2 * Math.sin(180 * Math.PI/180)

            PathAngleArc {
                centerX: root.width/2
                centerY: root.height/2
                radiusX: root.width/2 - root.lineWidth
                radiusY: root.height/2 - root.lineWidth
                startAngle: 180  // 起始角度
                sweepAngle: 180 * root.progress // 动态角度
            }
        }
    }

    // 红色指针（三角形）
    Rectangle {
        id: pointer
        width: 20
        height: 30
        color: pointerColor
        anchors.centerIn: parent
        antialiasing: true

        // 指针定位
        transform: Rotation {
            origin.x: width/2
            origin.y: height
            angle: root.progress * 360 - 90 // 动态旋转角度
        }

        // 三角形路径
        Canvas {
            anchors.fill: parent
            onPaint: {
                var ctx = getContext("2d")
                ctx.clearRect(0, 0, width, height)
                ctx.fillStyle = pointerColor
                ctx.beginPath()
                ctx.moveTo(0, height)
                ctx.lineTo(width/2, 0)
                ctx.lineTo(width, height)
                ctx.closePath()
                ctx.fill()
            }
        }

        // 指针动画同步
        Behavior on rotation {
            NumberAnimation {
                duration: 500
                easing.type: Easing.OutCubic
            }
        }
    }
}
