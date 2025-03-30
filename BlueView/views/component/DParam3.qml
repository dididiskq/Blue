import QtQuick 2.5
import QtQuick.Controls
import QtQuick.Layouts
Page
{
    Component.onCompleted:
    {

    }
    title: "温度参数"

    ParameterPage
    {
        width: parent.width
        paramList: [
            { name: "充电高温保护", value: 66, unit: "℃" },
            { name: "充电高温恢复", value: 66, unit: "℃" },
            { name: "充电低温保护",  value: -66, unit: "℃" },
            { name: "充电低温恢复",  value: -66, unit: "℃" },
            { name: "放电高温保护", value: 66, unit: "℃" },
            { name: "放电高温恢复", value: 66, unit: "℃" },
            { name: "放电低温保护",  value: -66, unit: "℃" },
            { name: "放电低温恢复",  value: -66, unit: "℃" },
        ]
    }
}
