import QtQuick 2.5
import QtQuick.Controls
import QtQuick.Layouts
Page
{
    background: Rectangle
    {
        color: "transparent"  // 完全透明
        // 或者半透明效果：color: "#80000000"
    }
    title: qsTr("快速设置")
    Connections
    {
        target: context
        function onMySignal(message)
        {
            if(message === "66")
            {
                print("改写成功")
            }
            else if(message === "-66")
            {
                print("改写超时")
            }
            else if(message === "-67")
            {
                print("服务或特征无效")
            }
        }
    }
    Column
    {
        id: colArea
        spacing: 10
        anchors
        {
            top: parent.top
            topMargin: srcDict.scaled(50)
            horizontalCenter: parent.horizontalCenter
        }
        Rectangle
        {
            height: srcDict.scaled(60)
            width: 300
            color: "#E4DDDD"
            radius: 10
            Label
            {
                text: qsTr("一键铁锂参数")
                anchors.centerIn: parent
                font.pixelSize: 16
                color: "#666666"
            }
        }

        Rectangle
        {
            height: srcDict.scaled(60)
            width: 300
            color: "#E4DDDD"
            radius: 10
            Label
            {
                text: qsTr("一键三元参数")
                anchors.centerIn: parent
                font.pixelSize: 16
                color: "#666666"
            }
        }


        Rectangle
        {
            height: srcDict.scaled(60)
            width: 300
            color: "#E4DDDD"
            radius: 10
            Label
            {
                text: qsTr("一键钠离子参数")
                anchors.centerIn: parent
                font.pixelSize: 16
                color: "#666666"
            }
        }
    }
    Component.onCompleted:
    {
        //获取本页面数据
        srcDict.sendToBlue(24)
        srcDict.sendToBlue(27)

    }

    // 示例页面：ChargeParamsPage.qml
    ParameterPage
    {
        anchors.top: colArea.bottom
        anchors.topMargin: 20
        width: parent.width
        paramList: [
            { name: qsTr("电池实际串数"), value: srcDict.cellNum === undefined ? 0 : srcDict.cellNum, unit: "串" , cellData: 512},
            { name: qsTr("电池物理容量"), value: srcDict.fcc === undefined ? 0 : srcDict.fcc/100, unit: "AH" , cellData: 1026}
        ]
    }
    /*

    Rectangle
    {
        anchors.top: colArea.bottom
        anchors.topMargin: srcDict.scaled(50)
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 50
        height: srcDict.scaled(210)
        // border.color: "red"
        // horizontalCenter: parent.horizontalCenter

        // 参数表格
        GridLayout
        {
            anchors.fill: parent
            columns: 3
            rows: 3
            columnSpacing: 0  // 消除列间距
            rowSpacing: 0    // 消除行间距
            Rectangle
            {
                height: parent.height / 3
                width: parent.width / 3
                // border.color: "red"
                Label
                {
                    anchors.centerIn: parent
                    text: "项目"
                }
            }
            Rectangle
            {
                height: parent.height / 3
                width: parent.width / 3
                // border.color: "red"
                Label
                {
                    anchors.centerIn: parent
                    text: "参数"
                }
            }
            Rectangle
            {
                height: parent.height / 3
                width: parent.width / 3
                // border.color: "red"
                Label
                {
                    anchors.centerIn: parent
                    text: "设定"
                }
            }
            Rectangle
            {
                height: parent.height / 3
                width: parent.width / 3
                // border.color: "red"
                Label
                {
                    anchors.centerIn: parent
                    text: "电池串数"
                }
            }
            Rectangle
            {
                height: parent.height / 3
                width: parent.width / 3
                border.color: "black"
                TextFieldTemplate
                {
                    id: cellNumInput
                    anchors.fill: parent
                    width: parent.width * 0.8
                    height: parent.height * 0.8
                }
            }
            Rectangle
            {
                height: parent.height / 3
                width: parent.width / 3
                // border.color: "red"
                Button
                {
                    anchors.centerIn: parent
                    width: parent.width * 0.8
                    height: parent.height * 0.8
                    text: "设置"
                    onClicked:
                    {
                        var inputDate = cellNumInput.inputObj.text
                        srcDict.writeToBlue(512, inputDate)
                    }
                }
            }
            Rectangle
            {
                height: parent.height / 3
                width: parent.width / 3
                // border.color: "red"
                Label
                {
                    anchors.centerIn: parent
                    text: "电池容量"
                }
            }
            Rectangle
            {
                height: parent.height / 3
                width: parent.width / 3
                border.color: "black"
                TextFieldTemplate
                {
                    anchors.fill: parent
                    width: parent.width * 0.8
                    height: parent.height * 0.8
                }
            }
            Rectangle
            {
                height: parent.height / 3
                width: parent.width / 3
                // border.color: "red"
                Button
                {
                    anchors.centerIn: parent
                    width: parent.width * 0.8
                    height: parent.height * 0.8
                    text: "设置"
                    onClicked:
                    {
                        var inputDate = cellNumInput.inputObj.text
                        // srcDict.writeToBlue(512, inputDate)
                    }
                }
            }

        }
    }

*/
}
