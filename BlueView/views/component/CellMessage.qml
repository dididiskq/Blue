import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
Page
{
    property var realProtect: srcDict.protectMap
    title: qsTr("电池信息")
    Component.onCompleted:
    {
        srcDict.sendToBlue(-560)
        srcDict.sendToBlue(-566)
        srcDict.sendToBlue(24)
        srcDict.sendToBlue(19)
        srcDict.sendToBlue(-536)
        srcDict.sendToBlue(-570)
        srcDict.sendToBlue(-582)
        srcDict.sendToBlue(-586)
        srcDict.sendToBlue(-598)
        srcDict.sendToBlue(-1024)
        srcDict.sendToBlue(-1032)
        srcDict.sendToBlue(27)
        srcDict.sendToBlue(28)
        srcDict.sendToBlue(29)
        srcDict.sendToBlue(30)
        srcDict.getProtectMessage(2)
    }

    ScrollView
    {
        id: root
        width: srcDict.winWidth
        height: srcDict.winHeight
        clip: true
        ColumnLayout
        {
            width: Math.max(implicitWidth, root.width)
            spacing: 20

            // 电池信息部分
            ColumnLayout
            {
                Layout.margins: 20
                spacing: 10
                id: columnLayout  // 添加 id

                function getCellType(type)
                {

                    if(type === undefined)
                    {
                        return qsTr("")
                    }
                    if(type === 0)
                    {
                        return qsTr("磷酸铁锂")
                    }
                    else if(type === 1)
                    {
                        return qsTr("钛酸锂")
                    }
                    else if(type === 2)
                    {
                        return qsTr("钠电池")
                    }
                }
                GridLayout
                {
                    columns: 2
                    columnSpacing: 20
                    rowSpacing: 8

                    // 电池信息项
                    Text { text: qsTr("电池 SN"); font.bold: true }
                    Text { text: srcDict.sn === undefined ? "" : srcDict.sn }

                    Text { text: qsTr("制造厂家"); font.bold: true }
                    Text { text: srcDict.manufacturer === undefined ? "" : srcDict.manufacturer }

                    Text { text: qsTr("制造厂商型号"); font.bold: true }
                    Text { text: srcDict.manufacturerMode === undefined ? "" : srcDict.manufacturerMode }

                    Text { text: qsTr("客户名称"); font.bold: true }
                    Text { text: srcDict.customerName === undefined ? "" : srcDict.customerName }

                    Text { text: qsTr("客户型号"); font.bold: true }
                    Text { text: srcDict.customerMode === undefined ? "" : srcDict.customerMode }

                    Text { text: qsTr("生产日期"); font.bold: true }
                    Text { text: srcDict.mnfDate === undefined ? "" : srcDict.mnfDate }

                    Text { text: qsTr("固件版本"); font.bold: true }
                    Text { text: srcDict.mainVer === undefined ? "" : srcDict.mainVer }

                    Text { text: qsTr("电池类型"); font.bold: true }
                    Text { text: columnLayout.getCellType(srcDict.celllType) }

                    Text { text: qsTr("电池串数"); font.bold: true }
                    Text { text: srcDict.cellNum === undefined ? 0 : srcDict.cellNum }


                    Text { text: qsTr("BMS时间"); font.bold: true }
                    Text { text: qsTr("2025-01-01 00:00") }

                    Text { text: qsTr("设计循环次数"); font.bold: true }
                    Text { text: srcDict.sjCirCount === undefined ? "" : srcDict.sjCirCount }

                    Text { text: qsTr("满充容量"); font.bold: true }
                    Text { text: srcDict.fcc === undefined ? "" : srcDict.fcc }

                    Text { text: qsTr("设计容量"); font.bold: true }
                    Text { text: srcDict.dc === undefined ? "" : srcDict.dc }

                    Text { text: qsTr("最大未充电间隔时间"); font.bold: true }
                    Text { text: srcDict.maxNoElect === undefined ? "" : srcDict.maxNoElect }

                    Text { text: qsTr("最近未充电间隔时间"); font.bold: true }
                    Text { text: srcDict.majNoElect === undefined ? "" : srcDict.majNoElect }

                    Text { text: qsTr("BT码"); font.bold: true }
                    Text { text: srcDict.bt === undefined ? "" : srcDict.bt }

                }
            }


            // 保护事件表格
            ColumnLayout
            {
                Layout.fillWidth: true
                spacing: 10

                // Text {
                //     text: "保护事件记录"
                //     font.bold: true
                //     font.pixelSize: 18
                //     Layout.leftMargin: 20
                // }

                // 表格头部
                RowLayout
                {
                    Layout.leftMargin: 20
                    Layout.rightMargin: 20
                    spacing: 0

                    Text
                    {
                        text: "保护时间"
                        font.bold: true
                        Layout.preferredWidth: 200
                        horizontalAlignment: Text.AlignLeft
                    }

                    Text
                    {
                        text: "保护事件"
                        font.bold: true
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignLeft
                    }
                }

                // 表格内容
                ListView
                {
                    id: eventList
                    Layout.fillWidth: true
                    Layout.preferredHeight: 400
                    model: eventModel
                    clip: true
                    spacing: 2

                    delegate: RowLayout
                    {
                        width: eventList.width
                        height: 30
                        spacing: 0

                        Text
                        {
                            text: eventTime
                            Layout.preferredWidth: 200
                            leftPadding: 20
                            verticalAlignment: Text.AlignVCenter
                        }

                        Text
                        {
                            text: eventCode
                            Layout.fillWidth: true
                            verticalAlignment: Text.AlignVCenter
                        }

                        Rectangle
                        {
                            height: 1
                            color: "#eee"
                            Layout.fillWidth: true
                        }
                    }
                }
            }
        }


    }
    ListModel
    {
        id: eventModel
    }
    // 动态添加数据的方法
    function addEvent(time, code)
    {
        eventModel.append({"eventTime": time, "eventCode": code})
    }
    onRealProtectChanged:
    {
        if(realProtect === undedfined)
        {
            return
        }
        addEvent(realProtect.protectTime, realProtect.protectEvent)
    }

    // Button
    // {
    //     text: "Add Event"
    //     onClicked: root.addEvent("2023-09-01 12:34:56", "0x00000001")
    // }
}
