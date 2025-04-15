import QtQuick
import QtQuick.Controls
Page
{
    title: qsTr("生产操作面板")

    Rectangle
    {
        id: rectangle
        anchors.top: parent.top
        anchors.topMargin: srcDict.scaled(50)
        width: parent.width
        height: srcDict.scaled(150)
        color: "#E4DDDD"
        radius: 10
        Label
        {
            anchors.centerIn: parent
            text: "电流归零"
        }
    }
    Rectangle
    {
        id: rectangle1
        anchors.top: rectangle.bottom
        anchors.topMargin: srcDict.scaled(50)
        width: parent.width
        height: srcDict.scaled(150)
        color: "#E4DDDD"
        radius: 10
        TextFieldTemplate
        {
            anchors
            {
                left: parent.left
                top: parent.top
                topMargin: (parent.height - height) / 2
                leftMargin: srcDict.scaled(30)
            }
            width: parent.width * 0.6
            height: parent.height * 0.3
            inputObj.placeholderText: "请输入蓝牙名称"
        }

        Label
        {
            anchors
            {
                right: parent.right
                top: parent.top
                topMargin: (parent.height - height) / 2
                rightMargin: srcDict.scaled(30)
            }

            text: "写入蓝牙名称"
        }
    }
    Rectangle
    {
        id: rectangle2
        anchors.top: rectangle1.bottom
        anchors.topMargin: srcDict.scaled(50)
        width: parent.width
        height: srcDict.scaled(150)
        color: "#E4DDDD"
        radius: 10
        Label
        {
            anchors.centerIn: parent
            text: "扫描条形码"
        }
    }

}
