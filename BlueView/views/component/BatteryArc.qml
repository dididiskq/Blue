import QtQuick
import QtQuick.Shapes

Item
{
    id: root
    width: srcDict.scaled(200)
    height: srcDict.scaled(200)

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
            startX: root.width/2 + root.width/2 * Math.cos(270 * Math.PI/180)
            startY: root.height/2 + root.height/2 * Math.sin(270 * Math.PI/180)

            PathAngleArc
            {
                centerX: root.width/2
                centerY: root.height/2
                radiusX: root.width/2 - root.lineWidth
                radiusY: root.height/2 - root.lineWidth
                startAngle: 135 // 起始角度（左上）
                sweepAngle: 270     // 总角度（270度）
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
            startX: root.width/2 + root.width/2 * Math.cos(270 * Math.PI/180)
            startY: root.height/2 + root.height/2 * Math.sin(270 * Math.PI/180)

            PathAngleArc {
                centerX: root.width/2
                centerY: root.height/2
                radiusX: root.width/2 - root.lineWidth
                radiusY: root.height/2 - root.lineWidth
                startAngle: 135  // 起始角度
                sweepAngle: 270 * root.progress // 动态角度
            }
        }
    }
    // 动态指针
    Rectangle
    {
        id: pointer
        z: 1
        width: 20
        height: parent.height / 2 - lineWidth
        color:  "transparent"
        anchors {
                horizontalCenter: parent.horizontalCenter
                bottom: parent.verticalCenter  // 将底部锚定到圆心
            }
        antialiasing: true
        border.color: "red"
        Image
        {
            anchors.fill: parent
            source:"../res/zhizhen.svg"
        }

        transformOrigin: Item.Bottom
        rotation:  -135 + 270 * root.progress  // 角度范围：-90°（左）到 90°（右）
    }
    // 中心文字
    Column {
        visible: false
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
