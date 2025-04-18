
import QtQuick
import QtQuick.Controls

Page {
    property var soc: srcDict.soc
    property var soh: srcDict.soh
    property var cellList: srcDict.cellVlist

    background: Rectangle
    {
        // color: "transparent"
        color: "white"
    }
    title: "实时数据"

    onCellListChanged:
    {
        if(cellList === undefined)
        {
            return
        }
        for (var i = 0; i < batteryModel.count; i++)
        {
            // console.log(i, cellList[i])
            var str = String(cellList[i]) + "V"; // 结果: "3.14"
            batteryModel.setProperty(i, "typeData", str)

        }
    }
    ListModel {
        id: batteryModel
        Component.onCompleted:
        {
            for (var i = 0; i < 32; i++)
            {

                append({text: "" + (i + 1), imgSrc: "../res/cellCom.svg", typeData: ""})
            }
        }
    }

    // 主内容容器
    Flickable
    {
        id: flickable
        anchors.fill: parent
        contentHeight: contentColumn.height // 动态计算总高度
        clip: true

        Column
        { // 垂直布局所有内容块
            id: contentColumn
            width: parent.width

            InfoGridOne
            {
            }

            // InfoGridLang
            // {
            // }

            // 电池信息
            InfoGrid
            {
                title: "电池信息"
                modelData: [
                    {text: "总电压", source: "../res/electY.png", data: srcDict.electYa === undefined ? "" : srcDict.electYa},
                    {text: "总电流", source: "../res/electL.png", data: srcDict.electLiu === undefined ? "" : srcDict.electLiu},
                    {text: "压差", source: "../res/electY.png", data: srcDict.yaCha === undefined ? "" : String(srcDict.yaCha)},
                    {text: "最高电压", source: "../res/maxYa.png", data: srcDict.maxYa === undefined ? "" : String(srcDict.maxYa)},
                    {text: "最低电压", source: "../res/minYa.png", data: srcDict.minYa === undefined ? "" : String(srcDict.minYa)},
                    {text: "循环次数", source: "../res/electY.png", data: srcDict.cycles_number === undefined ? "" : srcDict.cycles_number},
                    // {text: "功率", source: "../res/power.png", data: 33},
                ]
            }

            // 温度信息模块
            InfoGrid
            {
                title: "温度信息"
                modelData: [
                    {text: "MOS温度", source: "", data: srcDict.mosTemperature === undefined ? "" : srcDict.mosTemperature},
                    {text: "T1温度", source: "", data: srcDict.temperature1 === undefined ? "" : srcDict.temperature1},
                    {text: "T2温度", source: "", data: srcDict.temperature2 === undefined ? "" : srcDict.temperature2},
                    {text: "T3温度", source: "", data: srcDict.temperature3 === undefined ? "" : srcDict.temperature3}
                ]
            }

            // 电池单体电压
            Rectangle
            {
                width: parent.width
                height: batteryGrid.height + 40 // 标题高度
                color: "transparent"

                // 标题
                Text {
                    text: "单体电压"
                    font.pixelSize: 16
                    font.bold: true
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins: 10
                }

                // 电池单元专用网格布局
                GridView {
                    id: batteryGrid
                    width: parent.width
                    height: Math.ceil(model.count / 5) * cellHeight // 动态计算高度
                    anchors.top: parent.top
                    anchors.topMargin: 40
                    cellWidth: width / 5   // 关键：每行5个
                    cellHeight: 90
                    interactive: false     // 禁用独立滚动

                    model:batteryModel

                    delegate: Rectangle {
                        width: batteryGrid.cellWidth
                        height: batteryGrid.cellHeight
                        color: "transparent"
                        // border.color: "red"

                        Text
                        {
                            text: model.text
                            font.pixelSize: 12
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            anchors.top: parent.top
                        }
                        Text
                        {
                            text: model.typeData
                            font.pixelSize: 12
                            anchors.right: parent.right
                            anchors.top: parent.top
                        }

                        Image
                        {
                            source: model.imgSrc
                            // anchors.right: parent.right
                            // anchors.verticalCenter : parent.verticalCenter
                            anchors.bottom: parent.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: parent.width
                            height: 70
                        }
                    }
                }
            }
        }
    }
}
