import QtQuick 2.5
import QtQuick.Controls
import QtQuick.Layouts
Page
{
    Component.onCompleted:
    {

    }
    title: "电压参数"
    // 示例页面：ChargeParamsPage.qml
    ParameterPage
    {
        width: parent.width
        paramList: [
            { name: "过充保护电压", value: 3650, unit: "mV" },
            { name: "过充回复电压", value: 3350, unit: "mV" },
            { name: "过放保护电压",  value: 2300, unit: "mV" },
            { name: "过放恢复电压",  value: 2440, unit: "mV" },
        ]
    }
}
