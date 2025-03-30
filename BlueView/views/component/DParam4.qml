import QtQuick 2.5
import QtQuick.Controls
import QtQuick.Layouts
Page
{
    Component.onCompleted:
    {

    }
    title: "电流参数"
    ParameterPage
    {
        width: parent.width
        paramList: [
            { name: "充电过流1保护电流", value: 66, unit: "℃" },
            { name: "充电过流1延时", value: 66, unit: "℃" },
            { name: "放电过流1保护电流",  value: -66, unit: "℃" },
            { name: "放电过流1延时",  value: -66, unit: "℃" },
            { name: "放电过流2保护电流", value: 66, unit: "℃" },
            { name: "放电过流2延时", value: 66, unit: "℃" },
            { name: "短路保护电流",  value: -66, unit: "℃" },
            { name: "短路保护延时",  value: -66, unit: "℃" },
            { name: "采样电阻值",  value: -66, unit: "℃" },
        ]
    }
}
