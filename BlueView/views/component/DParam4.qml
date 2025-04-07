import QtQuick 2.5
import QtQuick.Controls
import QtQuick.Layouts
Page
{
    Component.onCompleted:
    {
        srcDict.sendToBlue(-544)
        srcDict.sendToBlue(-545)
        srcDict.sendToBlue(-538)
        srcDict.sendToBlue(-539)
        srcDict.sendToBlue(-540)
        srcDict.sendToBlue(-541)
        srcDict.sendToBlue(-542)
        srcDict.sendToBlue(-543)
        srcDict.sendToBlue(-526)
    }
    title: "电流参数"
    ParameterPage
    {
        width: parent.width
        paramList: [
            { name: "充电过流1保护电流", value: srcDict.occ === undefined ? 0 : srcDict.occ, unit: "℃", cellData:544},
            { name: "充电过流1延时", value: srcDict.occt === undefined ? 0 : srcDict.occt, unit: "℃", cellData:545},
            { name: "放电过流1保护电流",  value: srcDict.ocd1 === undefined ? 0 : srcDict.ocd1, unit: "℃", cellData:538},
            { name: "放电过流1延时",  value: srcDict.ocd1t === undefined ? 0 : srcDict.ocd1t, unit: "℃" , cellData:539},
            { name: "放电过流2保护电流", value: srcDict.ocd2 === undefined ? 0 : srcDict.ocd2, unit: "℃" , cellData:540},
            { name: "放电过流2延时", value: srcDict.ocd2t === undefined ? 0 : srcDict.ocd2t, unit: "℃" , cellData:541},
            { name: "短路保护电流",  value: srcDict.dbYa === undefined ? 0 : srcDict.dbYa, unit: "℃", cellData:542 },
            { name: "短路保护延时",  value: srcDict.sct === undefined ? 0 : srcDict.sct, unit: "℃" , cellData:543},
            { name: "采样电阻值",  value: srcDict.sampleRValue === undefined ? 0 : srcDict.sampleRValue, unit: "℃", cellData:526 },
        ]
    }
}
