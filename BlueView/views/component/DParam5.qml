import QtQuick 2.5
import QtQuick.Controls
import QtQuick.Layouts
Page
{
    Component.onCompleted:
    {

    }
    title: "均衡参数"
    ParameterPage
    {
        width: parent.width
        paramList: [
            { name: "均衡启动电压", value: 66, unit: "mV" },
            { name: "均衡启动阈值", value: 66, unit: "mV" },
            { name: "均衡延时",  value: -66, unit: "ms" },
        ]
    }
}
