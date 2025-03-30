import QtQuick 2.5
import QtQuick.Controls
import QtQuick.Layouts
Page
{
    Component.onCompleted:
    {

    }
    title: "系统参数"
    ParameterPage
    {
        width: parent.width
        paramList: [
            { name: "额定充电电压", value: 66, unit: "0.1V" },
            { name: "额定充电电流", value: 66, unit: "0.1A" },
            { name: "休眠延时",  value: -66, unit: "s" },
            { name: "关机延时",  value: -66, unit: "s" },
            { name: "满充延时", value: 66, unit: "s" },
            { name: "满充电压", value: 66, unit: "mV" },
            { name: "满充电流",  value: -66, unit: "mA" },
            { name: "零电流显示阈值",  value: -66, unit: "mA" },
        ]
    }
}

