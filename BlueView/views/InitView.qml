import QtQuick
import QtQuick.Controls
import "./component"
import "./js" as HMFunc
import QtQuick.Window
Item
{
    // 安全区域边距（通过 Screen 获取）
    readonly property real safeAreaTop: Screen.desktopAvailableHeight - Screen.height
    readonly property real safeAreaBottom: Screen.height - (Screen.desktopAvailableHeight + Screen.desktopAvailableY)
    TabBar
    {
        id: tabBar
        // focus: true

        visible: srcDict.isShowTool
        z: 1
        width: parent.width
        contentHeight: parent.height * 0.1
        anchors.bottom: parent.bottom
        currentIndex: swipeView.currentIndex

        STabButton
        {
            id: btnMain
            buttonText: "设置"
            sour.source: "../res/setIcon.svg"
            sourP.source: "../res/setIconP.svg"
            onClicked:
            {
                swipeView.currentIndex = 0
                devPage.realDrawer.close()
            }

        }
        STabButton
        {
            id: btnDevice
            buttonText: "实时"
            background: Rectangle
            {
                id:colorRect
                radius: 20
                color: "transparent"
                // border.color: "red"
                Image
                {
                    id: name1
                    height: srcDict.scaled(55)
                    width: srcDict.scaled(55)
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.leftMargin: srcDict.scaled(40)
                    visible: true
                    source: "res/cellIconP.svg"
                }
                Image
                {
                    id: name2
                    height: srcDict.scaled(55)
                    width: srcDict.scaled(55)
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.leftMargin: srcDict.scaled(40)
                    visible: false
                    source: "res/cellIcon.svg"
                }
            }
            onFocusChanged:
            {
                if (btnDevice.focus)
                {
                    name2.visible = true
                    name1.visible = false
                }
                else
                {
                    name1.visible = true
                    name2.visible = false
                }
            }
            onClicked:
            {
                swipeView.currentIndex = 1
                devPage.realDrawer.close()
            }
        }
        STabButton
        {
            id: btnMine
            buttonText: "我的"
            sour.source: "../res/mineIcon.svg"
            sourP.source: "../res/mineIconP.svg"
            onClicked:
            {
                swipeView.currentIndex = 2
                devPage.realDrawer.close()
            }

        }
    }
    SwipeView
    {
        id: swipeView
        currentIndex: 1
        // currentIndex: tabBar.currentIndex
        width: parent.width
        anchors.top: parent.top
        height: parent.height - tabBar.height
        interactive: false
        DevicePage
        {
            id: devPage
        }
        MainPage
        {
            onHidenTabbar: (type) =>
            {
                console.log("收到信号参数:", type)
                if(type === 1)
                {
                    tabBar.visible = false
                }
                else if(type === 0)
                {
                    tabBar.visible = true
                }
            }
        }

        MinePage
        {

        }

    }

    Component.onCompleted:
    {
        // 通过 QML 直接获取屏幕逻辑尺寸
        var physicalWidth = Screen.width;
        var physicalHeight = Screen.height;
        var logicalWidth = physicalWidth / Screen.devicePixelRatio;
        var logicalHeight = physicalHeight / Screen.devicePixelRatio;
        console.log("逻辑尺寸:", logicalWidth, logicalHeight);
    }
}
