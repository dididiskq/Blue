import QtQuick 2.5
import QtQuick.Controls
import QtQuick.Layouts
Page
{
    Component.onCompleted:
    {
        srcDict.sendToBlue(-546)
        srcDict.sendToBlue(-547)
        srcDict.sendToBlue(-548)
        srcDict.sendToBlue(-549)
        srcDict.sendToBlue(-550)
        srcDict.sendToBlue(-551)
        srcDict.sendToBlue(-552)
        srcDict.sendToBlue(-553)
    }
    title: "温度参数"

    ParameterPage
    {
        width: parent.width
        paramList: [
            { name: "充电高温保护", value: 66, unit: "℃", cellData: 546},
            { name: "充电高温恢复", value: 66, unit: "℃", cellData: 547},
            { name: "充电低温保护",  value: -66, unit: "℃", cellData: 548},
            { name: "充电低温恢复",  value: -66, unit: "℃", cellData: 549},
            { name: "放电高温保护", value: 66, unit: "℃", cellData: 550 },
            { name: "放电高温恢复", value: 66, unit: "℃", cellData: 551 },
            { name: "放电低温保护",  value: -66, unit: "℃",cellData: 552 },
            { name: "放电低温恢复",  value: -66, unit: "℃",cellData: 553 },
        ]
    }
}
