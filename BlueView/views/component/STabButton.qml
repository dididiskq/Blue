import QtQuick 2.5
import QtQuick.Controls
//通用按钮模板
TabButton
{

    id:tabbutton1
    property int  buttonTextPointSize: 10
    property color pressBackgroundColor: "lightgreen"
    property color releaseBackgroundColor: "transparent"
    property alias sour: name1
    property alias sourP: name2
    property string buttonText: ""
    background: Rectangle
    {
        id:colorRect
        radius: 20
        color: "transparent"
        Image
        {
            id: name1
            height: srcDict.scaled(40)
            width: srcDict.scaled(40)
            anchors.centerIn: parent
            visible: true
            source: ""
        }
        Image
        {
            id: name2
            height: srcDict.scaled(40)
            width: srcDict.scaled(40)
            anchors.centerIn: parent
            visible: false
            source: ""
        }
    }
    onFocusChanged:
    {
        if (tabbutton1.focus)
        {
            name2.visible = true
            name1.visible = false
        }
        else
        {
            name1.visible = true
            name2.visible = false
        }
    }
    Label
    {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: srcDict.scaled(8)
        anchors.left: parent.left
        anchors.leftMargin: srcDict.scaled(52)
        text: buttonText
        font.pointSize: buttonTextPointSize
    }


}
