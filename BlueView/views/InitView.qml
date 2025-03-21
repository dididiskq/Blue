import QtQuick
import QtQuick.Controls
import "./component"
import "./js" as HMFunc
import QtQuick.Window
Item
{
    TabBar
    {
        id: tabBar
        // focus: true
        width: parent.width
        contentHeight: parent.height * 0.1
        anchors.bottom: parent.bottom
        currentIndex: swipeView.currentIndex
        background: Rectangle
        {
            color: "#d6e1c2" // 标签按钮背景透明
        }
        STabButton
        {
            id: btnMain
            buttonText: "首页"
            onClicked:
            {
                currIndex = 1
                devPage.realDrawer.close()
            }

        }
        STabButton
        {
            id: btnDevice
            buttonText: "设备"
            onClicked:
            {
                currIndex = 2
                devPage.realDrawer.close()
            }
        }
        STabButton
        {
            id: btnMine
            buttonText: "我的"
            onClicked:
            {
                currIndex = 3
                devPage.realDrawer.close()
            }

        }
    }
    SwipeView
    {
        id: swipeView
        currentIndex: tabBar.currentIndex
        width: parent.width
        anchors.top: parent.top
        height: parent.height - tabBar.height
        interactive: false

        MainPage
        {
            onHidenTabbar: (type)=>
            {
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
        DevicePage
        {
            id: devPage
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
