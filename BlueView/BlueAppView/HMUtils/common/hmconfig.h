#ifndef HMCONFIG_H
#define HMCONFIG_H
namespace HMConfig {
// 代码声明
enum HASCARD {
    NO_CARD=0,
    EN_CSC,
    EX_CSC,
    TCU_CSC,
    EN_QR,
    EX_QR,
    TCU_QR,
    EN_EMV,
    EX_EMV,
};

enum EFCPVIEWCONFIG{
    TouchOctopusOrCreditCardToProcessor = 1,
    TouchOctopusToProcessor,
    TouchCreaditCardToProcessor,
    NotInUse,
    EMV_AcceptedForFirstClassTravel,
    EMV_NoEntryRexcord,
    EMV_InvalidCard,
    EMV_TouchCardToProcessorAgain,
    EMV_UseOneCardOnly,
    EMV_PleaseWait,
    OCTOPUS_AcceptedForFirstClassTravel,
    OCTOPUS_NoEntryRexcord,
    OCTOPUS_InvalidCard,
    OCTOPUS_TouchCardToProcessorAgain,
    OCTOPUS_UseOneCardOnly,
    OCTOPUS_PleaseWait,
    SVG_Test,
};

enum QRCODETYPE{
    SJQR = 0,
    ALIPAY,
};

enum GATETYPE{
    AGM_EN = 0,         //单向进站
    AGM_EX,             //单向出站(不带回收)
    AGM_EX_TT,          //单向出站(带回收)
    AGM_BOTH,           //双向进出(不带回收)
    AGM_BOTH_TT ,       //双向进出(带回收)
    AGM_BOTH_EN = 1,
    AGM_BOTH_EX_TT = 2,
};

enum AISLEMODE{
    NORMAL_CLOSED ,//扇门常闭
    NORMAL_OPENED,
    NORMAL_OPENED_EN ,//扇门常开进站方向
    NORMAL_OPENED_EX ,//扇门常开进站方向

};

enum GCUMODE{
    GCU_MODE_ENT = 1,		//1-进站
    GCU_MODE_EXT,			//2-出站
    GCU_MODE_DUO,			//3-双向
    GCU_MODE_ENT_CLOSE_EXT,	//4-出站禁止，进站放行
    GCU_MODE_EXT_CLOSE_ENT,	//5-出站放行，进站禁止
    GCU_MODE_EXT_CHECK_ENT,	//6-出站放行，进站刷卡
    GCU_MODE_ENT_CHECK_EXT,	//7-出站刷卡，进站放行
    GCU_MODE_CLOSE,			//8-关闭
    GCU_MODE_MAINTAIN,		//9-维护
    GCU_MODE_ERROR,         //10-故障
    GCU_MODE_FREE,			//11-自由
    GCU_MODE_EMERGENCY,		//12-紧急(默认填3)
};

enum FAREMODE{
    FARE_MODE_NORMAL             = 0,     //正常
    FARE_MODE_TMO_BIT            = 0x0001,//延时模式，会把一切和计时有关的时间延长，例如早折扣是7:15到8:20，当开启此模式后，早折扣时间变成7:15到9:00,不需要针对处理
    FARE_MODE_EEO_BIT            = 0x0002,//不使用
    FARE_MODE_HOLIDAY_BIT        = 0x0004,//节假日（不使用）
    FARE_MODE_INCIDENT_BIT       = 0x0008,//免费通行，有对应画面
    FARE_MODE_GOODWILL_BIT       = 0x0010,//不使用
    FARE_MODE_HIGHSECURITY_BIT   = 0x0020,//可通过本地或远程设置高安全模式，配合正常票价模式或延时模式使用
    FARE_MODE_DELAY_OPER_BIT     = 0x0040,//不使用
    FARE_MODE_FAIL_TRAIN_BIT     = 0x0080,//不使用
};

enum GATEMODE{
    NONE   = -1,    //无
    NORMAL = 0 ,    //正常服务
    PAUSE,          //暂停服务
    MAINTENANCE,    //维修模式
    EMERGENCY,      //紧急模式
    FREE,           //自由放行
    STOP,           //停止服务

    EN_NO_FAIL_EX_NO_FAIL = 50,     //(进站)无故障|(出站)无故障
    EN_NO_FAIL_EX_CSC_FAIL,        //(进站)无故障|(出站)八达通读写器故障
    EN_NO_FAIL_EX_QR_FAIL,              //(进站)无故障|(出站)二维码读写器故障
    EN_NO_FAIL_EX_EMV_FAIL,             //(进站)无故障|(出站)信用卡读写器故障
    EN_NO_FAIL_EX_TTCSC_FAIL,           //(进站)无故障|(回收)八达通读写器故障
    EN_NO_FAIL_EX_TTQR_FAIL,            //(进站)无故障|(回收)二维码读写器故障
    EN_NO_FAIL_EX_CSC_QR_FAIL,     //(进站)无故障|(出站)八达通读写器&&(出站)二维码读写器故障
    EN_NO_FAIL_EX_CSC_EMV_FAIL,    //(进站)无故障|(出站)八达通读写器&&(出站)信用卡读写器故障
    EN_NO_FAIL_EX_CSC_TTCSC_FAIL,  //(进站)无故障|(出站)八达通读写器&&(回收)八达通读写器故障
    EN_NO_FAIL_EX_CSC_TTQR_FAIL,   //(进站)无故障|(出站)八达通读写器&&(回收)二维码读写器故障
    EN_NO_FAIL_EX_QR_EMV_FAIL,     //(进站)无故障|(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_NO_FAIL_EX_QR_TTCSC_FAIL,   //(进站)无故障|(出站)二维码读写器&&(回收)八达通读写器故障
    EN_NO_FAIL_EX_QR_TTQR_FAIL,    //(进站)无故障|(出站)二维码读写器&&(回收)二维码读写器故障
    EN_NO_FAIL_EX_EMV_TTCSC_FAIL,  //(进站)无故障|(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_NO_FAIL_EX_EMV_TTQR_FAIL,   //(进站)无故障|(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_NO_FAIL_EX_TTCSC_TTQR_FAIL, //(进站)无故障|(回收)八达通读写器&&(回收)二维码读写器故障
    EN_NO_FAIL_EX_CSC_QR_EMV_FAIL,     //(进站)无故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_NO_FAIL_EX_CSC_QR_TTCSC_FAIL,   //(进站)无故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器故障
    EN_NO_FAIL_EX_CSC_QR_TTQR_FAIL,    //(进站)无故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)二维码读写器故障
    EN_NO_FAIL_EX_CSC_EMV_TTCSC_FAIL,  //(进站)无故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_NO_FAIL_EX_CSC_EMV_TTQR_FAIL,   //(进站)无故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_NO_FAIL_EX_CSC_TTCSC_TTQR_FAIL, //(进站)无故障|(出站)八达通读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_NO_FAIL_EX_QR_EMV_TTCSC_FAIL,   //(进站)无故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_NO_FAIL_EX_QR_EMV_TTQR_FAIL,    //(进站)无故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_NO_FAIL_EX_QR_TTCSC_TTQR_FAIL,  //(进站)无故障|(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_NO_FAIL_EX_EMV_TTCSC_TTQR_FAIL, //(进站)无故障|(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_NO_FAIL_EX_CSC_QR_EMV_TTCSC_FAIL,     //(进站)无故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_NO_FAIL_EX_CSC_QR_EMV_TTQR_FAIL,      //(进站)无故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_NO_FAIL_EX_CSC_QR_TTCSC_TTQR_FAIL,    //(进站)无故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_NO_FAIL_EX_CSC_EMV_TTCSC_TTQR_FAIL,   //(进站)无故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_NO_FAIL_EX_QR_EMV_TTCSC_TTQR_FAIL,    //(进站)无故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_NO_FAIL_EX_CSC_QR_EMV_TTCSC_TTQR_FAIL,     //(进站)无故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障


    EN_CSC_FAIL_EX_NO_FAIL,         //(进站)八达通读写器故障|(出站)无故障
    EN_CSC_FAIL_EX_CSC_FAIL,        //(进站)八达通读写器故障|(出站)八达通读写器故障
    EN_CSC_FAIL_EX_QR_FAIL,         //(进站)八达通读写器故障|(出站)二维码读写器故障
    EN_CSC_FAIL_EX_EMV_FAIL,        //(进站)八达通读写器故障|(出站)信用卡读写器故障
    EN_CSC_FAIL_EX_TTCSC_FAIL,      //(进站)八达通读写器故障|(回收)八达通读写器故障
    EN_CSC_FAIL_EX_TTQR_FAIL,       //(进站)八达通读写器故障|(回收)二维码读写器故障
    EN_CSC_FAIL_EX_CSC_QR_FAIL,     //(进站)八达通读写器故障|(出站)八达通读写器&&(出站)二维码读写器故障
    EN_CSC_FAIL_EX_CSC_EMV_FAIL,    //(进站)八达通读写器故障|(出站)八达通读写器&&(出站)信用卡读写器故障
    EN_CSC_FAIL_EX_CSC_TTCSC_FAIL,  //(进站)八达通读写器故障|(出站)八达通读写器&&(回收)八达通读写器故障
    EN_CSC_FAIL_EX_CSC_TTQR_FAIL,   //(进站)八达通读写器故障|(出站)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_FAIL_EX_QR_EMV_FAIL,     //(进站)八达通读写器故障|(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_CSC_FAIL_EX_QR_TTCSC_FAIL,   //(进站)八达通读写器故障|(出站)二维码读写器&&(回收)八达通读写器故障
    EN_CSC_FAIL_EX_QR_TTQR_FAIL,    //(进站)八达通读写器故障|(出站)二维码读写器&&(回收)二维码读写器故障
    EN_CSC_FAIL_EX_EMV_TTCSC_FAIL,  //(进站)八达通读写器故障|(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_FAIL_EX_EMV_TTQR_FAIL,   //(进站)八达通读写器故障|(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_FAIL_EX_TTCSC_TTQR_FAIL, //(进站)八达通读写器故障|(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_FAIL_EX_CSC_QR_EMV_FAIL,     //(进站)八达通读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_CSC_FAIL_EX_CSC_QR_TTCSC_FAIL,   //(进站)八达通读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器故障
    EN_CSC_FAIL_EX_CSC_QR_TTQR_FAIL,    //(进站)八达通读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)二维码读写器故障
    EN_CSC_FAIL_EX_CSC_EMV_TTCSC_FAIL,  //(进站)八达通读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_FAIL_EX_CSC_EMV_TTQR_FAIL,   //(进站)八达通读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_FAIL_EX_CSC_TTCSC_TTQR_FAIL, //(进站)八达通读写器故障|(出站)八达通读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_FAIL_EX_QR_EMV_TTCSC_FAIL,   //(进站)八达通读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_FAIL_EX_QR_EMV_TTQR_FAIL,    //(进站)八达通读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_FAIL_EX_QR_TTCSC_TTQR_FAIL,  //(进站)八达通读写器故障|(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_FAIL_EX_EMV_TTCSC_TTQR_FAIL, //(进站)八达通读写器故障|(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_FAIL_EX_CSC_QR_EMV_TTCSC_FAIL,     //(进站)八达通读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_FAIL_EX_CSC_QR_EMV_TTQR_FAIL,      //(进站)八达通读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_FAIL_EX_CSC_QR_TTCSC_TTQR_FAIL,    //(进站)八达通读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_FAIL_EX_CSC_EMV_TTCSC_TTQR_FAIL,   //(进站)八达通读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_FAIL_EX_QR_EMV_TTCSC_TTQR_FAIL,    //(进站)八达通读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_FAIL_EX_CSC_QR_EMV_TTCSC_TTQR_FAIL,     //(进站)八达通读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障


    EN_QR_FAIL_EX_NO_FAIL,         //(进站)二维码读写器故障|(出站)无故障
    EN_QR_FAIL_EX_CSC_FAIL,        //(进站)二维码读写器故障|(出站)八达通读写器故障
    EN_QR_FAIL_EX_QR_FAIL,         //(进站)二维码读写器故障|(出站)二维码读写器故障
    EN_QR_FAIL_EX_EMV_FAIL,        //(进站)二维码读写器故障|(出站)信用卡读写器故障
    EN_QR_FAIL_EX_TTCSC_FAIL,      //(进站)二维码读写器故障|(回收)八达通读写器故障
    EN_QR_FAIL_EX_TTQR_FAIL,       //(进站)二维码读写器故障|(回收)二维码读写器故障
    EN_QR_FAIL_EX_CSC_QR_FAIL,     //(进站)二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器故障
    EN_QR_FAIL_EX_CSC_EMV_FAIL,    //(进站)二维码读写器故障|(出站)八达通读写器&&(出站)信用卡读写器故障
    EN_QR_FAIL_EX_CSC_TTCSC_FAIL,  //(进站)二维码读写器故障|(出站)八达通读写器&&(回收)八达通读写器故障
    EN_QR_FAIL_EX_CSC_TTQR_FAIL,   //(进站)二维码读写器故障|(出站)八达通读写器&&(回收)二维码读写器故障
    EN_QR_FAIL_EX_QR_EMV_FAIL,     //(进站)二维码读写器故障|(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_QR_FAIL_EX_QR_TTCSC_FAIL,   //(进站)二维码读写器故障|(出站)二维码读写器&&(回收)八达通读写器故障
    EN_QR_FAIL_EX_QR_TTQR_FAIL,    //(进站)二维码读写器故障|(出站)二维码读写器&&(回收)二维码读写器故障
    EN_QR_FAIL_EX_EMV_TTCSC_FAIL,  //(进站)二维码读写器故障|(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_QR_FAIL_EX_EMV_TTQR_FAIL,   //(进站)二维码读写器故障|(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_QR_FAIL_EX_TTCSC_TTQR_FAIL, //(进站)二维码读写器故障|(回收)八达通读写器&&(回收)二维码读写器故障
    EN_QR_FAIL_EX_CSC_QR_EMV_FAIL,     //(进站)二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_QR_FAIL_EX_CSC_QR_TTCSC_FAIL,   //(进站)二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器故障
    EN_QR_FAIL_EX_CSC_QR_TTQR_FAIL,    //(进站)二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)二维码读写器故障
    EN_QR_FAIL_EX_CSC_EMV_TTCSC_FAIL,  //(进站)二维码读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_QR_FAIL_EX_CSC_EMV_TTQR_FAIL,   //(进站)二维码读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_QR_FAIL_EX_CSC_TTCSC_TTQR_FAIL, //(进站)二维码读写器故障|(出站)八达通读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_QR_FAIL_EX_QR_EMV_TTCSC_FAIL,   //(进站)二维码读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_QR_FAIL_EX_QR_EMV_TTQR_FAIL,    //(进站)二维码读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_QR_FAIL_EX_QR_TTCSC_TTQR_FAIL,  //(进站)二维码读写器故障|(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_QR_FAIL_EX_EMV_TTCSC_TTQR_FAIL, //(进站)二维码读写器故障|(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_QR_FAIL_EX_CSC_QR_EMV_TTCSC_FAIL,     //(进站)二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_QR_FAIL_EX_CSC_QR_EMV_TTQR_FAIL,      //(进站)二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_QR_FAIL_EX_CSC_QR_TTCSC_TTQR_FAIL,    //(进站)二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_QR_FAIL_EX_CSC_EMV_TTCSC_TTQR_FAIL,   //(进站)二维码读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_QR_FAIL_EX_QR_EMV_TTCSC_TTQR_FAIL,    //(进站)二维码读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_QR_FAIL_EX_CSC_QR_EMV_TTCSC_TTQR_FAIL,     //(进站)二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障


    EN_EMV_FAIL_EX_NO_FAIL,         //(进站)信用卡读写器故障|(出站)无故障
    EN_EMV_FAIL_EX_CSC_FAIL,        //(进站)信用卡读写器故障|(出站)八达通读写器故障
    EN_EMV_FAIL_EX_QR_FAIL,         //(进站)信用卡读写器故障|(出站)二维码读写器故障
    EN_EMV_FAIL_EX_EMV_FAIL,        //(进站)信用卡读写器故障|(出站)信用卡读写器故障
    EN_EMV_FAIL_EX_TTCSC_FAIL,      //(进站)信用卡读写器故障|(回收)八达通读写器故障
    EN_EMV_FAIL_EX_TTQR_FAIL,       //(进站)信用卡读写器故障|(回收)二维码读写器故障
    EN_EMV_FAIL_EX_CSC_QR_FAIL,     //(进站)信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器故障
    EN_EMV_FAIL_EX_CSC_EMV_FAIL,    //(进站)信用卡读写器故障|(出站)八达通读写器&&(出站)信用卡读写器故障
    EN_EMV_FAIL_EX_CSC_TTCSC_FAIL,  //(进站)信用卡读写器故障|(出站)八达通读写器&&(回收)八达通读写器故障
    EN_EMV_FAIL_EX_CSC_TTQR_FAIL,   //(进站)信用卡读写器故障|(出站)八达通读写器&&(回收)二维码读写器故障
    EN_EMV_FAIL_EX_QR_EMV_FAIL,     //(进站)信用卡读写器故障|(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_EMV_FAIL_EX_QR_TTCSC_FAIL,   //(进站)信用卡读写器故障|(出站)二维码读写器&&(回收)八达通读写器故障
    EN_EMV_FAIL_EX_QR_TTQR_FAIL,    //(进站)信用卡读写器故障|(出站)二维码读写器&&(回收)二维码读写器故障
    EN_EMV_FAIL_EX_EMV_TTCSC_FAIL,  //(进站)信用卡读写器故障|(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_EMV_FAIL_EX_EMV_TTQR_FAIL,   //(进站)信用卡读写器故障|(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_EMV_FAIL_EX_TTCSC_TTQR_FAIL, //(进站)信用卡读写器故障|(回收)八达通读写器&&(回收)二维码读写器故障
    EN_EMV_FAIL_EX_CSC_QR_EMV_FAIL,     //(进站)信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_EMV_FAIL_EX_CSC_QR_TTCSC_FAIL,   //(进站)信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器故障
    EN_EMV_FAIL_EX_CSC_QR_TTQR_FAIL,    //(进站)信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)二维码读写器故障
    EN_EMV_FAIL_EX_CSC_EMV_TTCSC_FAIL,  //(进站)信用卡读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_EMV_FAIL_EX_CSC_EMV_TTQR_FAIL,   //(进站)信用卡读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_EMV_FAIL_EX_CSC_TTCSC_TTQR_FAIL, //(进站)信用卡读写器故障|(出站)八达通读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_EMV_FAIL_EX_QR_EMV_TTCSC_FAIL,   //(进站)信用卡读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_EMV_FAIL_EX_QR_EMV_TTQR_FAIL,    //(进站)信用卡读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_EMV_FAIL_EX_QR_TTCSC_TTQR_FAIL,  //(进站)信用卡读写器故障|(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_EMV_FAIL_EX_EMV_TTCSC_TTQR_FAIL, //(进站)信用卡读写器故障|(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_EMV_FAIL_EX_CSC_QR_EMV_TTCSC_FAIL,     //(进站)信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_EMV_FAIL_EX_CSC_QR_EMV_TTQR_FAIL,      //(进站)信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_EMV_FAIL_EX_CSC_QR_TTCSC_TTQR_FAIL,    //(进站)信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_EMV_FAIL_EX_CSC_EMV_TTCSC_TTQR_FAIL,   //(进站)信用卡读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_EMV_FAIL_EX_QR_EMV_TTCSC_TTQR_FAIL,    //(进站)信用卡读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_EMV_FAIL_EX_CSC_QR_EMV_TTCSC_TTQR_FAIL,     //(进站)信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障

    EN_CSC_QR_FAIL_EX_NO_FAIL,         //(进站)八达通读写器&&二维码读写器故障|(出站)无故障
    EN_CSC_QR_FAIL_EX_CSC_FAIL,        //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器故障
    EN_CSC_QR_FAIL_EX_QR_FAIL,         //(进站)八达通读写器&&二维码读写器故障|(出站)二维码读写器故障
    EN_CSC_QR_FAIL_EX_EMV_FAIL,        //(进站)八达通读写器&&二维码读写器故障|(出站)信用卡读写器故障
    EN_CSC_QR_FAIL_EX_TTCSC_FAIL,      //(进站)八达通读写器&&二维码读写器故障|(回收)八达通读写器故障
    EN_CSC_QR_FAIL_EX_TTQR_FAIL,       //(进站)八达通读写器&&二维码读写器故障|(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_CSC_QR_FAIL,     //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器故障
    EN_CSC_QR_FAIL_EX_CSC_EMV_FAIL,    //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(出站)信用卡读写器故障
    EN_CSC_QR_FAIL_EX_CSC_TTCSC_FAIL,  //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(回收)八达通读写器故障
    EN_CSC_QR_FAIL_EX_CSC_TTQR_FAIL,   //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_QR_EMV_FAIL,     //(进站)八达通读写器&&二维码读写器故障|(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_CSC_QR_FAIL_EX_QR_TTCSC_FAIL,   //(进站)八达通读写器&&二维码读写器故障|(出站)二维码读写器&&(回收)八达通读写器故障
    EN_CSC_QR_FAIL_EX_QR_TTQR_FAIL,    //(进站)八达通读写器&&二维码读写器故障|(出站)二维码读写器&&(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_EMV_TTCSC_FAIL,  //(进站)八达通读写器&&二维码读写器故障|(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_QR_FAIL_EX_EMV_TTQR_FAIL,   //(进站)八达通读写器&&二维码读写器故障|(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_TTCSC_TTQR_FAIL, //(进站)八达通读写器&&二维码读写器故障|(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_CSC_QR_EMV_FAIL,     //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_CSC_QR_FAIL_EX_CSC_QR_TTCSC_FAIL,   //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器故障
    EN_CSC_QR_FAIL_EX_CSC_QR_TTQR_FAIL,    //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_CSC_EMV_TTCSC_FAIL,  //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_QR_FAIL_EX_CSC_EMV_TTQR_FAIL,   //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_CSC_TTCSC_TTQR_FAIL, //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_QR_EMV_TTCSC_FAIL,   //(进站)八达通读写器&&二维码读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_QR_FAIL_EX_QR_EMV_TTQR_FAIL,    //(进站)八达通读写器&&二维码读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_QR_TTCSC_TTQR_FAIL,  //(进站)八达通读写器&&二维码读写器故障|(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_EMV_TTCSC_TTQR_FAIL, //(进站)八达通读写器&&二维码读写器故障|(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_CSC_QR_EMV_TTCSC_FAIL,     //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_QR_FAIL_EX_CSC_QR_EMV_TTQR_FAIL,      //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_CSC_QR_TTCSC_TTQR_FAIL,    //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_CSC_EMV_TTCSC_TTQR_FAIL,   //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_QR_EMV_TTCSC_TTQR_FAIL,    //(进站)八达通读写器&&二维码读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_FAIL_EX_CSC_QR_EMV_TTCSC_TTQR_FAIL,     //(进站)八达通读写器&&二维码读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障


    EN_CSC_EMV_FAIL_EX_NO_FAIL,         //(进站)八达通读写器&&信用卡读写器故障|(出站)无故障
    EN_CSC_EMV_FAIL_EX_CSC_FAIL,        //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器故障
    EN_CSC_EMV_FAIL_EX_QR_FAIL,         //(进站)八达通读写器&&信用卡读写器故障|(出站)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_EMV_FAIL,        //(进站)八达通读写器&&信用卡读写器故障|(出站)信用卡读写器故障
    EN_CSC_EMV_FAIL_EX_TTCSC_FAIL,      //(进站)八达通读写器&&信用卡读写器故障|(回收)八达通读写器故障
    EN_CSC_EMV_FAIL_EX_TTQR_FAIL,       //(进站)八达通读写器&&信用卡读写器故障|(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_QR_FAIL,     //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_EMV_FAIL,    //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)信用卡读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_TTCSC_FAIL,  //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(回收)八达通读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_TTQR_FAIL,   //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_QR_EMV_FAIL,     //(进站)八达通读写器&&信用卡读写器故障|(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_CSC_EMV_FAIL_EX_QR_TTCSC_FAIL,   //(进站)八达通读写器&&信用卡读写器故障|(出站)二维码读写器&&(回收)八达通读写器故障
    EN_CSC_EMV_FAIL_EX_QR_TTQR_FAIL,    //(进站)八达通读写器&&信用卡读写器故障|(出站)二维码读写器&&(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_EMV_TTCSC_FAIL,  //(进站)八达通读写器&&信用卡读写器故障|(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_EMV_FAIL_EX_EMV_TTQR_FAIL,   //(进站)八达通读写器&&信用卡读写器故障|(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_TTCSC_TTQR_FAIL, //(进站)八达通读写器&&信用卡读写器故障|(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_QR_EMV_FAIL,     //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_QR_TTCSC_FAIL,   //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_QR_TTQR_FAIL,    //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_EMV_TTCSC_FAIL,  //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_EMV_TTQR_FAIL,   //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_TTCSC_TTQR_FAIL, //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_QR_EMV_TTCSC_FAIL,   //(进站)八达通读写器&&信用卡读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_EMV_FAIL_EX_QR_EMV_TTQR_FAIL,    //(进站)八达通读写器&&信用卡读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_QR_TTCSC_TTQR_FAIL,  //(进站)八达通读写器&&信用卡读写器故障|(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_EMV_TTCSC_TTQR_FAIL, //(进站)八达通读写器&&信用卡读写器故障|(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_QR_EMV_TTCSC_FAIL,     //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_QR_EMV_TTQR_FAIL,      //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_QR_TTCSC_TTQR_FAIL,    //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_EMV_TTCSC_TTQR_FAIL,   //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_QR_EMV_TTCSC_TTQR_FAIL,    //(进站)八达通读写器&&信用卡读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_EMV_FAIL_EX_CSC_QR_EMV_TTCSC_TTQR_FAIL,     //(进站)八达通读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障


    EN_QR_EMV_FAIL_EX_NO_FAIL,         //(进站)二维码读写器&&信用卡读写器故障|(出站)无故障
    EN_QR_EMV_FAIL_EX_CSC_FAIL,        //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器故障
    EN_QR_EMV_FAIL_EX_QR_FAIL,         //(进站)二维码读写器&&信用卡读写器故障|(出站)二维码读写器故障
    EN_QR_EMV_FAIL_EX_EMV_FAIL,        //(进站)二维码读写器&&信用卡读写器故障|(出站)信用卡读写器故障
    EN_QR_EMV_FAIL_EX_TTCSC_FAIL,      //(进站)二维码读写器&&信用卡读写器故障|(回收)八达通读写器故障
    EN_QR_EMV_FAIL_EX_TTQR_FAIL,       //(进站)二维码读写器&&信用卡读写器故障|(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_CSC_QR_FAIL,     //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器故障
    EN_QR_EMV_FAIL_EX_CSC_EMV_FAIL,    //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)信用卡读写器故障
    EN_QR_EMV_FAIL_EX_CSC_TTCSC_FAIL,  //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(回收)八达通读写器故障
    EN_QR_EMV_FAIL_EX_CSC_TTQR_FAIL,   //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_QR_EMV_FAIL,     //(进站)二维码读写器&&信用卡读写器故障|(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_QR_EMV_FAIL_EX_QR_TTCSC_FAIL,   //(进站)二维码读写器&&信用卡读写器故障|(出站)二维码读写器&&(回收)八达通读写器故障
    EN_QR_EMV_FAIL_EX_QR_TTQR_FAIL,    //(进站)二维码读写器&&信用卡读写器故障|(出站)二维码读写器&&(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_EMV_TTCSC_FAIL,  //(进站)二维码读写器&&信用卡读写器故障|(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_QR_EMV_FAIL_EX_EMV_TTQR_FAIL,   //(进站)二维码读写器&&信用卡读写器故障|(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_TTCSC_TTQR_FAIL, //(进站)二维码读写器&&信用卡读写器故障|(回收)八达通读写器&&(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_CSC_QR_EMV_FAIL,     //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_QR_EMV_FAIL_EX_CSC_QR_TTCSC_FAIL,   //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器故障
    EN_QR_EMV_FAIL_EX_CSC_QR_TTQR_FAIL,    //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_CSC_EMV_TTCSC_FAIL,  //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_QR_EMV_FAIL_EX_CSC_EMV_TTQR_FAIL,   //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_CSC_TTCSC_TTQR_FAIL, //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_QR_EMV_TTCSC_FAIL,   //(进站)二维码读写器&&信用卡读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_QR_EMV_FAIL_EX_QR_EMV_TTQR_FAIL,    //(进站)二维码读写器&&信用卡读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_QR_TTCSC_TTQR_FAIL,  //(进站)二维码读写器&&信用卡读写器故障|(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_EMV_TTCSC_TTQR_FAIL, //(进站)二维码读写器&&信用卡读写器故障|(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_CSC_QR_EMV_TTCSC_FAIL,     //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_QR_EMV_FAIL_EX_CSC_QR_EMV_TTQR_FAIL,      //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_CSC_QR_TTCSC_TTQR_FAIL,    //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_CSC_EMV_TTCSC_TTQR_FAIL,   //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_QR_EMV_TTCSC_TTQR_FAIL,    //(进站)二维码读写器&&信用卡读写器故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_QR_EMV_FAIL_EX_CSC_QR_EMV_TTCSC_TTQR_FAIL,     //(进站)二维码读写器&&信用卡读写器故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障


    EN_CSC_QR_EMV_FAIL_EX_NO_FAIL,         //进站端读写器均故障|(出站)无故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_FAIL,        //进站端读写器均故障|(出站)八达通读写器故障
    EN_CSC_QR_EMV_FAIL_EX_QR_FAIL,         //进站端读写器均故障|(出站)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_EMV_FAIL,        //进站端读写器均故障|(出站)信用卡读写器故障
    EN_CSC_QR_EMV_FAIL_EX_TTCSC_FAIL,      //进站端读写器均故障|(回收)八达通读写器故障
    EN_CSC_QR_EMV_FAIL_EX_TTQR_FAIL,       //进站端读写器均故障|(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_QR_FAIL,     //进站端读写器均故障|(出站)八达通读写器&&(出站)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_EMV_FAIL,    //进站端读写器均故障|(出站)八达通读写器&&(出站)信用卡读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_TTCSC_FAIL,  //进站端读写器均故障|(出站)八达通读写器&&(回收)八达通读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_TTQR_FAIL,   //进站端读写器均故障|(出站)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_QR_EMV_FAIL,     //进站端读写器均故障|(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_CSC_QR_EMV_FAIL_EX_QR_TTCSC_FAIL,   //进站端读写器均故障|(出站)二维码读写器&&(回收)八达通读写器故障
    EN_CSC_QR_EMV_FAIL_EX_QR_TTQR_FAIL,    //进站端读写器均故障|(出站)二维码读写器&&(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_EMV_TTCSC_FAIL,  //进站端读写器均故障|(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_QR_EMV_FAIL_EX_EMV_TTQR_FAIL,   //进站端读写器均故障|(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_TTCSC_TTQR_FAIL, //进站端读写器均故障|(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_QR_EMV_FAIL,     //进站端读写器均故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_QR_TTCSC_FAIL,   //进站端读写器均故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_QR_TTQR_FAIL,    //进站端读写器均故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_EMV_TTCSC_FAIL,  //进站端读写器均故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_EMV_TTQR_FAIL,   //进站端读写器均故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_TTCSC_TTQR_FAIL, //进站端读写器均故障|(出站)八达通读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_QR_EMV_TTCSC_FAIL,   //进站端读写器均故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_QR_EMV_FAIL_EX_QR_EMV_TTQR_FAIL,    //进站端读写器均故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_QR_TTCSC_TTQR_FAIL,  //进站端读写器均故障|(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_EMV_TTCSC_TTQR_FAIL, //进站端读写器均故障|(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_QR_EMV_TTCSC_FAIL,     //进站端读写器均故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_QR_EMV_TTQR_FAIL,      //进站端读写器均故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_QR_TTCSC_TTQR_FAIL,    //进站端读写器均故障|(出站)八达通读写器&&(出站)二维码读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_EMV_TTCSC_TTQR_FAIL,   //进站端读写器均故障|(出站)八达通读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_QR_EMV_TTCSC_TTQR_FAIL,    //进站端读写器均故障|(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障
    EN_CSC_QR_EMV_FAIL_EX_CSC_QR_EMV_TTCSC_TTQR_FAIL,     //进站端读写器均故障|(出站)八达通读写器&&(出站)二维码读写器&&(出站)信用卡读写器&&(回收)八达通读写器&&(回收)二维码读写器故障

};

enum MessageType{
    JSON_TRANSACTION_CSC = 0            ,
    //JSON_UNCONF_TRANSACTION_CSC = (0x80 + 0) ,
    JSON_TRANSACTION_CASH=1             ,
    JSON_TRANSACTION_CSC_CASH           ,
    JSON_TRANSACTION_CSVT               ,
    JSON_TRANSACTION_KCRT               ,
    JSON_TRANSACTION_SR             	,
    JSON_ADD_VALUE_CASH             	,
    JSON_ADD_VALUE_EFT              	,
    JSON_AUTOPAY                    	,
    //JSON_UNCONF_AUTOPAY=(0x80 + 8),
    JSON_PASS_USAGE=9                   ,
    JSON_SPARE_1                    	,
    JSON_SPARE_2                    	,
    JSON_AUTOPAY_ENABLE             	,
    JSON_AUTOPAY_DISABLE            	,
    JSON_EVENT                      	,
    JSON_LOGIN                      	,
    JSON_LOGIN_NAME                 	,
    JSON_LOGOUT                     	,
    JSON_TRIP                       	,
    JSON_BLOCKING_BIT_SET           	,
    JSON_HIGH_SECURITY_VIOLATION    	,
    JSON_VAULT_PULL                 	,
    JSON_CSC_WRITE_THRESHOLD        	,
    JSON_SPARE_3                    	,
    JSON_FREE_EXIT                  	,
    JSON_CORRUPT                    	,
    JSON_PATRON_TRANSFER            	,
    JSON_VAULT_INSERT               	,
    JSON_CSC_ANON_ISSUE             	,
    JSON_CSC_INITIALISE1            	,
    JSON_BLOCKING_BIT_CLEAR         	,
    JSON_CSC_INIT_FAILURE           	,
    JSON_CSC_PERS_ISSUE                 ,
    JSON_CSC_PERS_PNAME             	,
    JSON_CSC_PERS_DETAILS           	,
    JSON_CSC_PERS_TRANSACTION       	,
    JSON_CSC_PERS_CNAME             	,
    JSON_CSC_LOWU_ISSUE             	,
    JSON_CSC_INITIALISE2            	,
    JSON_CSC_SURCHARGE              	,
    JSON_CASH_SURCHARGE             	,
    JSON_CSC_KEY_CHANGE             	,
    JSON_CSC_ANTI_PASSBACK_SET      	,
    JSON_CSC_ANTI_PASSBACK_CLEAR    	,
    JSON_CSC_TIME_EXPIRED           	,
    JSON_HYF_MAG_TXN                	,
    JSON_CSC_PERS_FAILURE           	,
    JSON_CSC_RETENTION              	,
    JSON_CSC_REFUND1                	,
    JSON_CSC_REFUND2                	,
    JSON_CSC_REFUND3                	,
    JSON_PASS_ISSUE                 	,
    JSON_SUP_FARE_CSC_ISSUE         	,
    JSON_SUP_FARE_CASH_ISSUE        	,
    JSON_NON_CSC_SALE_CSC           	,
    JSON_NON_CSC_SALE_CASH          	,
    JSON_SOUVENIR_SALE_CSC          	,
    JSON_SOUVENIR_SALE_CASH         	,
    JSON_LOWU_CHANGE_CASH           	,
    JSON_KCRER_FIRST_CLASS          	,
    JSON_NON_CSC_REFUND             	,
    JSON_OCP_CASH_OUT_FLOW          	,
    JSON_PASS_USAGE_CASH            	,
    JSON_PASS_ISSUE_CASH            	,
    JSON_OCP_START_SHIFT            	,
    JSON_OCP_END_SHIFT              	,
    JSON_OCP_ADD_VALUE              	,
    JSON_POST_TRANSACTION_CSC1      	,
    JSON_POST_TRANSACTION_CSC2      	,
    JSON_POST_TRANSACTION_CASH      	,
    JSON_CSC_REFUND4                	,
    JSON_CSC_REFUND5                	,
    JSON_AIR_TICKET_PURCHASE_CSC    	,
    JSON_AIR_TICKET_PURCHASE_CASH   	,
    JSON_LOG_PRINT_FEE_CSC              ,
    JSON_LOG_PRINT_FEE_CASH             ,
    JSON_EXCESS_FARE_CSC            	,
    JSON_EXCESS_FARE_CASH           	,
    JSON_LOWU_CHANGE_CSC            	,
    JSON_SJSC_TXN = 90                  ,
    JSON_SJSC_BLACKLISTED= 92           ,
    JSON_SJSC_RETAIN                    ,
    JSON_SJSC_INFO_UPDATE_PAYMENT       ,
    JSON_SJSC_REDEEM                    ,
    JSON_MONTHLY_PASS_HANDLE_PAYMENT    ,
    JSON_CSC_ADD_CASH_FAILURE_ENCASH    ,
    JSON_EXTRA_EVENT = 114              ,
    JSON_INACTIVE_CSC_ADM_FEE           ,
    JSON_INACTIVE_CSC_ADM_FEE_FAILURE   ,
    JSON_SJSC_SALES = 119               ,
    JSON_EPAYMENT                       ,
    JSON_EXCHANGE_RATE_SET = 123        ,
    JSON_UNCONF_TRANSACTION_CSC =128    ,
    JSON_UNCONF_AUTOPAY = 136           ,
    JSON_UNCONF_CSC_SURCHARGE = 167     ,
    JSON_UNCONF_SUP_FARE_CSC_ISSUE=180  ,
    JSON_UNCONF_NON_CSC_SALE_CSC=182    ,
    JSON_UNCONF_SOUVENIR_SALE_CSC = 184 ,
    JSON_UNCONF_INACTIVE_CSC_ADM_FEE=243,
    JSON_UNCONF_EXCHANGE_RATE_SET=251   ,
    JSON_SJQR_ISSUE_PAYMENT = 500       ,
    JSON_OCTOPUS_ADD_VALUEV =502        ,
    JSON_UNCONF_OCTOPUS_ADD_VALUE       ,
    JSON_OCP_OCTOPUS_ADD_VALUE          ,
    JSON_TRANSACTION_EMV =506           ,
    JSON_TRANSACTION_SJQR               ,
    JSON_EFCP_EMV                       ,
    JSON_EFCP_CSC                       ,
    JSON_UNCONF_EFCP_CSC                ,
    JSON_SURCHARGE                      ,
    JSON_SOUVENIR_SALE                  ,
    JSON_NON_CSC_SALE                   ,
    JSON_SUP_FARE_ISSUE                 ,
    JSON_LOG_PRINT_FEE                  ,
    JSON_EXCESS_FARE                    ,
    JSON_AIR_TICKET_PURCHASE            ,
    JSON_LOWU_CHANGE                    ,
    JSON_SJQR_REFUND_PAYMENT =520       ,
    JSON_SJQR_FIXING_PAYMENT            ,
    JSON_SJQR_REQUEST_REFUND=522        ,
    JSON_EMV_PAYG_REQUEST_REFUND        ,
    JSON_QRT_PAYG_REQUEST_REFUND        ,
    JSON_EMV_FIXING                     ,
    JSON_QRT_FIXING,
    JSON_EMV_SETTLE_BADDEBT,
    JSON_EMV_MANUAL_PREAUTH,
    JSON_PAYMENT_REQUEST_REFUND,
    JSON_TRM_SJSC_ISSUE=1216,
    JSON_TRM_SJSC_EXCESS_FARE_SURCHARGE,
    JSON_TRM_SJSC_RETAIN,
    JSON_TRM_SJSC_REDEEM,
    JSON_GENERAL_SURCHARGE,
    JSON_PCIS_CSC_BASEDATE=1222,
    JSON_BONUS_POINT_REDEEM_CASH =1226,
    JSON_BONUS_POINT_REDEEM_CSC ,
    JSON_DISCOUNT_SCHEME,
    JSON_CSC_ADD_VALUE_ADJUSTMENT =1231,
    JSON_VOUCHER_SUMMARY =1233,
    JSON_VOUCHER_DETAIL,
    JSON_BILL_PAYMENT,
    JSON_PRODUCT_RETURN,
    JSON_VOID_TRANSACTION,
    JSON_LARAD_AUDIT_DATA_2,
    JSON_CSC_ANTI_PASSBACK_SET_2,
    JSON_CSC_ANTI_PASSBACK_CLEAR_2,
    JSON_CSC_ANTI_PASSBACK_CLEAR_WAIVE_2,
    JSON_BILL_PAYMENT_2 = 1243,
    JSON_LARAD_AUDIT_DATA_3 ,
    JSON_TEMP_CARD_DETAIL ,
    JSON_TEMP_CARD_DETAIL_OTP,
    JSON_XB_GROUP_FARE_SALES_EVENT,
    JSON_BARCODE_EVENT,
    JSON_CUCFORM_ISSUE  =1251,
    JSON_CUCFORM_WITH_PATRONINFO_ISSUE =1253,
    JSON_ACTIVATE_PWD_RENEWAL_BIT_REQUEST =1256,
    JSON_ACTIVATE_RCD_RENEWAL_BIT_REQUEST = 1259,
    JSON_SMALL_AMOUNT_REFUND =1262,
    JSON_CSC_RETENTION_WITH_BARCODE,
    JSON_CSC_REFUND_WITH_BARCODE ,
    JSON_PCIS_CUC_PAYMENT_CONFIRM =1266,
    JSON_CUCFORM_CONFIRM=1271,
    JSON_ACTIVATE_RENEWAL_BIT_REQUEST=1278,
    JSON_ODD_DOLLAR_ADD_VALUE,
    JSON_TOAS_BLOCKING_BIT_SET ,
    JSON_TOAS_BLOCKING_BIT_CLEAR,
    JSON_TOAS_CSC_REFUND,
    JSON_TOAS_CSC_ANON_ISSUE,
    JSON_TOAS_CSC_RETENTION,
    JSON_TOAS_SJSC_RETENTION,

};

}
#endif // HMCONFIG_H
