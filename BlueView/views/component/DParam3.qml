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
            { name: "充电高温保护", value: srcDict.otc === undefined ? 0 : srcDict.otc, unit: "℃", cellData: 546},
            { name: "充电高温恢复", value: srcDict.otcr === undefined ? 0 : srcDict.otcr, unit: "℃", cellData: 547},
            { name: "充电低温保护",  value: srcDict.utc === undefined ? 0 : srcDict.utc, unit: "℃", cellData: 548},
            { name: "充电低温恢复",  value: srcDict.utcr === undefined ? 0 : srcDict.utcr, unit: "℃", cellData: 549},
            { name: "放电高温保护", value: srcDict.otd === undefined ? 0 : srcDict.otd, unit: "℃", cellData: 550 },
            { name: "放电高温恢复", value: srcDict.otdr === undefined ? 0 : srcDict.otdr, unit: "℃", cellData: 551 },
            { name: "放电低温保护",  value: srcDict.utd === undefined ? 0 : srcDict.utd, unit: "℃",cellData: 552 },
            { name: "放电低温恢复",  value: srcDict.utdr === undefined ? 0 : srcDict.utdr, unit: "℃",cellData: 553 },
        ]
    }
}
