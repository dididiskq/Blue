import QtQuick 2.5
import QtQuick.Controls
import QtQuick.Layouts
Page
{
    Component.onCompleted:
    {
        srcDict.sendToBlue(-520)
        srcDict.sendToBlue(-521)
        srcDict.sendToBlue(-528)
        srcDict.sendToBlue(-529)
        srcDict.sendToBlue(-524)
        srcDict.sendToBlue(-522)
        srcDict.sendToBlue(-523)
        srcDict.sendToBlue(-525)
    }
    title: "系统参数"
    ParameterPage
    {
        width: parent.width
        paramList: [
            { name: "额定充电电压", value: 66, unit: "0.1V", cellData:520 },
            { name: "额定充电电流", value: 66, unit: "0.1A", cellData:521 },
            { name: "休眠延时",  value: -66, unit: "s", cellData:518 },
            { name: "关机延时",  value: -66, unit: "s", cellData:519 },
            { name: "满充延时", value: 66, unit: "s", cellData:524 },
            { name: "满充电压", value: 66, unit: "mV", cellData:522 },
            { name: "满充电流",  value: -66, unit: "mA", cellData:523 },
            { name: "零电流显示阈值",  value: -66, unit: "mA", cellData:525 },
        ]
    }
}

