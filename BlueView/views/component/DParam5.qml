import QtQuick 2.5
import QtQuick.Controls
import QtQuick.Layouts
Page
{
    Component.onCompleted:
    {
        srcDict.sendToBlue(-532)
        srcDict.sendToBlue(-533)
        srcDict.sendToBlue(-534)
    }
    title: "均衡参数"
    ParameterPage
    {
        width: parent.width
        paramList: [
            { name: "均衡启动电压", value: srcDict.vob === undefined ? 0 : srcDict.vob, unit: "mV", cellData:532 },
            { name: "均衡启动阈值", value: srcDict.bald === undefined ? 0 : srcDict.bald, unit: "mV", cellData:533 },
            { name: "均衡延时",  value: srcDict.balt === undefined ? 0 : srcDict.balt, unit: "ms", cellData:534 },
        ]
    }
}
