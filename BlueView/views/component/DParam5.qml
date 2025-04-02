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
            { name: "均衡启动电压", value: 66, unit: "mV", cellData:532 },
            { name: "均衡启动阈值", value: 66, unit: "mV", cellData:533 },
            { name: "均衡延时",  value: -66, unit: "ms", cellData:534 },
        ]
    }
}
