
import QtQuick 2.15
import QtQuick.Layouts 1.15

ColumnLayout
{
    property var paramList: []      // 参数数据模型（JSON数组）
    property var temBtnText: "设置"
    property var celldata: ""
    property var userInput: ""
    // signal sentToPop(var celldata, var userInput)
    // 表头
    RowLayout {
        Layout.fillWidth: true
        Text { text: qsTr("项目"); font.bold: true; Layout.preferredWidth: 150 }
        Text { text: qsTr("参数"); font.bold: true; Layout.preferredWidth: 150 }
        Text { text: qsTr("设定"); font.bold: true; Layout.preferredWidth: 150 }
    }
    // onSentToPop:
    // {

    // }

    PasswordDialog
    {
        id: passwordDialog
        x: 50
        y: 200
        title: "安全验证"
        message: "请输入管理员密码"
        onConfirmed: (pwd) =>
        {
            console.log("输入密码:", pwd)
            if(pwd)
            {
                var item = repeater.itemAt(srcDict.itemIndex)
                item.btnText = "请稍后..."
                srcDict.writeToBlue(celldata, userInput)
                passwordDialog.close()
            }
            else
            {
                passwordDialog.message = "密码错误请重新输入"
            }
        }
        onCanceled: console.log("操作取消")
    }
    // 动态生成参数项
    Repeater
    {
        id: repeater
        model: paramList
        delegate: ParameterItem {
            paramName: modelData.name       // 数据模型字段：name
            paramValue: modelData.value     // 数据模型字段：value
            paramUnit: modelData.unit || "℃"// 默认单位为℃

            onClicked:
            {
                console.log("设置参数：", modelData.name, modelData.cellData, realValueEditor.text);
                srcDict.itemIndex = index
                celldata = modelData.cellData
                userInput = realValueEditor.text
                passwordDialog.open()
            }
        }
    }
    Connections
    {
        target: context
        function onMySignal(message)
        {
            var item = repeater.itemAt(srcDict.itemIndex)
            if(message === "66")
            {
                item.btnText = "设置成功"
                item.resetTimer.start()
            }
            else if(message === "-66")
            {
                item.btnText = "超时失败"
                item.resetTimer.start()
            }
            else if(message === "-67")
            {
                item.btnText = "服务无效"
                item.resetTimer.start()
            }
        }
    }

}

