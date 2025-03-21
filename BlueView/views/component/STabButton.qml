import QtQuick 2.5
import QtQuick.Controls
//通用按钮模板
TabButton
{

    id:tabbutton1
    property int  buttonTextPointSize: 15
    property color pressBackgroundColor: "lightgreen"
    property color releaseBackgroundColor: "transparent"

    property string buttonText: ""
    background: Rectangle
    {
        id:colorRect
        color: activeFocus ? "lightgreen" : "transparent"
        border.color:"royalblue"
        border.width: 1
        radius: 20
    }
    Label
    {
        anchors.centerIn: parent
        text: buttonText
        font.pointSize: buttonTextPointSize
    }
    onFocusChanged:
    {
        if (tabbutton1.focus)
        {
            // tabbutton1.scale = 1.2
            colorRect.color = "lightgreen"
        }
        else
        {
            // tabbutton1.scale = 1.0
            colorRect.color = "transparent"
        }
    }

}
