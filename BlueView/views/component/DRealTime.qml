import QtQuick 2.5
import QtQuick.Controls
Page
{
    property var soc: srcDict.soc
    property var soh: srcDict.soh
    background: Rectangle
    {
        color: "#d6e1c2"  // 设置背景颜色
        anchors.fill: parent // 确保填充整个 Page
    }

    title: "实时数据"
    Rectangle
    {
        border.color: "red"
        width: parent.width
        height: 550
        // x: 50
        y: 230
        Flickable
        {
            id: fliclable
            width: parent.width
            height: parent.height
            contentHeight: grid.height  // 关键：内容高度绑定子项总高度
            contentWidth: grid.width
            clip: true  // 裁剪超出区域
            Grid
            {
                id: grid
                // rows: 12 //行数
                // columns: 3 //列数
                width: fliclable.width

                Repeater
                {
                    model: listModel
                    delegate: Rectangle
                    {
                        height: (model.name === "title" || model.text === "") ? 40 :90
                        width: parent.width / 4
                        // border.color: "red"
                        Text
                        {
                            id: _text1
                            text: model.text
                            font.pixelSize: (model.name === "title") ? 16:12
                            font.bold: (model.name === "title")
                        }
                        Image
                        {
                            anchors.right: parent.right
                            height: (model.type === "battery") ? 85 : 50
                            width:  (model.type === "battery") ? 100 : 50
                            source: model.imgSrc
                        }
                    }
                }
            }
        }
    }


    /*动态加载
    Rectangle
    {
        border.color: "red"
        width: 351
        height: 466
        x: 50
        y: 50
        GridView
        {
            id: gridView
            anchors.fill: parent
            cellHeight: 80
            cellWidth: 117
            model: listModel
            delegate: Rectangle
            {
                border.color: "red"
                height: gridView.cellHeight
                width: gridView.cellWidth
                Text
                {
                    id: _text1
                    text: model.text
                    font.pixelSize: 12
                }
            }
        }
    }
    */
    ListModel
    {
        id: listModel
        ListElement
        {
            text: "电池信息"
            name: "title"
            type: ""
        }
        ListElement
        {
            text: ""
            type: ""
        }
        ListElement
        {
            text: ""
            type: ""
        }
        ListElement
        {
            text: ""
            type: ""
        }
        ListElement
        {
            text: "总电压"
            imgSrc: "../res/electY.png"
            type: ""
        }
        ListElement
        {
            text: "电流"
            imgSrc: "../res/electL.png"
            type: ""
        }
        ListElement
        {
            text: "功率"
            imgSrc: "../res/power.png"
            type: ""
        }
        ListElement
        {
            text: "最高电压"
            imgSrc: "../res/maxYa.png"
            type: ""
        }
        ListElement
        {
            text: "最低电压"
            imgSrc: "../res/minYa.png"
            type: ""
        }
        ListElement
        {
            text: "平均电压"
            imgSrc: "../res/average.png"
            type: ""
        }
        ListElement
        {
            text: "压差"
            imgSrc: ""
            type: ""
        }
        ListElement
        {
            text: "循环次数"
            imgSrc: ""
            type: ""
        }
        ListElement
        {
            text: "温度信息"
            name: "title"
            type: ""
        }
        ListElement
        {
            text: ""
            type: ""
        }
        ListElement
        {
            text: ""
            type: ""
        }
        ListElement
        {
            text: ""
            type: ""
        }
        ListElement
        {
            text: "MOS温度"
            imgSrc: ""
            type: ""
        }
        ListElement
        {
            text: "T1温度"
            imgSrc: ""
            type: ""
        }
        ListElement
        {
            text: "T2温度"
            imgSrc: ""
            type: ""
        }
        ListElement
        {
            text: "T3温度"
            imgSrc: ""
            type: ""
        }
        ListElement
        {
            text: "单体电压"
            name: "title"
            type: ""
        }
        ListElement
        {
            text: ""
            type: ""
        }
        ListElement
        {
            text: ""
            type: ""
        }
        ListElement
        {
            text: ""
            type: ""
        }
        Component.onCompleted:
        {
            //srcDict.cellNum
            for(var i = 0; i < 24; i++)
            {
                listModel.append({text: "No." + (i + 1), imgSrc: "../res/cellIcom.png", type: "battery"})
            }
        }
    }



    Rectangle
    {
        id: rectangle
        x: 6
        y: 6
        width: 439
        height: 212
        color: "#ffffff"

        Rectangle {
            id: rectangle1
            x: 8
            y: 8
            width: 200
            height: 196
            border.color: "red"
            color: "#ffffff"

            Label
            {
                x: 18
                y: 151
                width: 157
                height: 30
                text: "11:22:33:44:55:66"
                font.pixelSize: 15
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter // 关键修改：水平居中
                // anchors.centerIn: parent
            }
            Rectangle
            {
                width: parent.width
                height: 130
                border.color: "green"
                Image
                {
                    x: 4
                    y: 0
                    anchors.fill: parent
                    width: 192
                    height: 108
                    source: "../res/cellDev.png"
                }
                Label
                {
                    text: "我是电量显示"
                    anchors.centerIn: parent
                }
            }
        }
        Rectangle
        {
            id: rectangle2
            x: 233
            y: 8
            width: 200
            height: 196
            border.color: "red"
            color: "#ffffff"

        }

        Rectangle {
            border.color: "red"
            id: rectangle3
            x: 251
            y: 28
            width: 165
            height: 48
            color: "#ffffff"
        }
        Rectangle {
            border.color: "red"
            id: rectangle4
            x: 251
            y: 136
            width: 165
            height: 48
            color: "#ffffff"
        }
        Rectangle {
            id: rectangle5
            border.color: "red"
            x: 251
            y: 82
            width: 165
            height: 48
            color: "#ffffff"
        }

    }


}
