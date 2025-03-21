import QtQuick 2.5
import QtQml 2.2



QtObject
{
    property int winWidth: fields["winWidth"]
    property int winHeight: fields["winHeight"]
    property variant isShowVoiceImg: fields["isShow"]
    property variant blueDataReal: fields["blueData"]

    property var soc: fields["soc"]
    property var soh: fields["soh"]
    property var electYa: fields["electYa"]
    property var electLiu: fields["electLiu"]
    property var cMos: fields["cMos"]
    property var fMos: fields["fMos"]
    property var celllType: fields["celllType"]
    property var cellNum: fields["cellNum"]
    property var codeData: fields["codeData"]

    property bool isShowTool: true

    function startSearch()
    {
        var data = {}
        putOp("start.search.blue", data)
    }
    function sendToBlue(type)
    {
        var data = {}
        data["type"] = type
        putOp("send.to.blue", data)
    }
    function sendCodeData(codeData)
    {
        var data = {}
        data["codeData"] = codeData
        putOp("send.codeData", data)
    }
    function connectBlue(addr)
    {
        var data = {}
        data["addr"] = addr
        putOp("connect.blue", data)
    }
}
