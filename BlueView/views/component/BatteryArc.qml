import QtQuick
import QtQuick.Shapes

Item
{
    id: root
    width: srcDict.scaled(300)
    height: srcDict.scaled(300)

    // 可配置属性
    property real progress: 0.8    // 进度值（0-1）
    property int lineWidth: 20     // 进度条粗细
    property color backgroundColor: "#1A73E8"  // 背景色（原图蓝色）
    property color progressColor: "white"       // 进度条颜色
    property string textPrefix: "正在充电"       // 文字前缀

    // 进度动画（500ms缓动动画）
    Behavior on progress
    {
        NumberAnimation
        {
            duration: 500
            easing.type: Easing.OutCubic
        }
    }

    // 背景圆环
    Shape
    {
        anchors.fill: parent
        antialiasing: true
        ShapePath
        {
            strokeWidth: root.lineWidth
            strokeColor: Qt.lighter(root.backgroundColor, 1.2)
            capStyle: ShapePath.RoundCap
            fillColor: "transparent"
            startX: root.width/2 + root.width/2 * Math.cos(180 * Math.PI/180)
            startY: root.height/2 + root.height/2 * Math.sin(180 * Math.PI/180)

            PathAngleArc
            {
                centerX: root.width/2
                centerY: root.height/2
                radiusX: root.width/2 - root.lineWidth
                radiusY: root.height/2 - root.lineWidth
                startAngle: 180 // 起始角度（左上）
                sweepAngle: 180   // 总角度（270度）
            }
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

    // 中心文字
    Column {
        anchors.centerIn: parent
        spacing: 8

        Text {
            text: root.textPrefix
            color: "white"
            font.pixelSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: Math.round(root.progress * 100) + "%"
            color: "white"
            font {
                pixelSize: 42
                bold: true
                family: "Arial"
            }
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
