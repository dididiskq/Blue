#include "bmsprotocol.h"

// 寄存器地址到参数名的映射表（示例部分）
static QMap<quint16, QString> registerMap = {
    {0x0000, "MOS温度1"},
    {0x0001, "电池温度1"},
    {0x0014, "SOC_SOH"},
    // 添加其他寄存器映射...
};

BMSProtocol::BMSProtocol(QObject *parent) : QObject(parent)
{
    commands[0x0000] = [this](const QByteArray& data, int dataLen) { return deal_00(data, dataLen); };
    commands[0x0001] = [this](const QByteArray& data, int dataLen) { return deal_01(data, dataLen); };
    commands[0x0002] = [this](const QByteArray& data, int dataLen) { return deal_02(data, dataLen); };
    commands[0x0003] = [this](const QByteArray& data, int dataLen) { return deal_03(data, dataLen); };
    commands[0x0004] = [this](const QByteArray& data, int dataLen) { return deal_04(data, dataLen); };
    commands[0x0006] = [this](const QByteArray& data, int dataLen) { return deal_06(data, dataLen); };
    commands[0x0008] = [this](const QByteArray& data, int dataLen) { return deal_08(data, dataLen); };
    commands[0x000A] = [this](const QByteArray& data, int dataLen) { return deal_0A(data, dataLen); };
    commands[0x000C] = [this](const QByteArray& data, int dataLen) { return deal_0C(data, dataLen); };
    commands[0x000E] = [this](const QByteArray& data, int dataLen) { return deal_0E(data, dataLen); };
    commands[0x000F] = [this](const QByteArray& data, int dataLen) { return deal_0F(data, dataLen); };
    commands[0x0010] = [this](const QByteArray& data, int dataLen) { return deal_10(data, dataLen); };
    commands[0x0011] = [this](const QByteArray& data, int dataLen) { return deal_11(data, dataLen); };
    commands[0x0014] = [this](const QByteArray& data, int dataLen) { return deal_14(data, dataLen); };
    commands[0x0015] = [this](const QByteArray& data, int dataLen) { return deal_15(data, dataLen); };
    commands[0x000C] = [this](const QByteArray& data, int dataLen) { return deal_0C(data, dataLen); };
    commands[0x0018] = [this](const QByteArray& data, int dataLen) { return deal_18(data, dataLen); };
    commands[0x001B] = [this](const QByteArray& data, int dataLen) { return deal_1B(data, dataLen); };
    commands[0x0020] = [this](const QByteArray& data, int dataLen) { return deal_20(data, dataLen); };

}
//封装报文
QByteArray BMSProtocol::byte(const QVariant &v)
{
    QVariantMap params = v.toMap();
    QByteArray frame;

    // 基础帧结构
    quint8 address = params.value("address", 0x16).toUInt(); // 默认地址0x16
    quint8 funcCode = params.value("funcCode").toUInt();

    frame.append(address);
    frame.append(funcCode);

    // 功能码分支处理
    if(funcCode == 0x03)// 读寄存器
    {
        quint16 startAddr = params.value("startAddr").toUInt();
        quint16 regCount = params.value("regCount").toUInt();

        startAddr &= 0xFFFF;
        regCount &= 0xFFFF;

        frame.append(static_cast<char>((startAddr >> 8) & 0xFF)); // 高字节
        frame.append(static_cast<char>(startAddr & 0xFF)); // 低字节
        frame.append(static_cast<char>((regCount >> 8) & 0xFF));
        frame.append(static_cast<char>(regCount & 0xFF));
    }
    else if(funcCode == 0x10)// 写寄存器
    {
        quint16 startAddr = params.value("startAddr").toUInt();
        quint16 regCount = params.value("regCount").toUInt();
        QByteArray data = params.value("data").toByteArray();

        frame.append(static_cast<char>(startAddr >> 8));
        frame.append(static_cast<char>(startAddr & 0xFF));
        frame.append(static_cast<char>(regCount >> 8));
        frame.append(static_cast<char>(regCount & 0xFF));
        frame.append(static_cast<char>(data.size()));
        frame.append(data);
    }

    // 计算CRC并附加
    quint16 crc = calculateCRC(frame);
    crc &= 0xFFFF;
    frame.append(static_cast<char>(crc & 0xFF)); // 低字节在前
    frame.append(static_cast<char>((crc >> 8) & 0xFF));// 高字节在后

    return frame;
}
//解析报文
QVariantMap BMSProtocol::parse(const QByteArray& buf)
{
    QVariantMap result;
    if(buf.size() < 5)// 最小帧长度校验
    {
        result.insert("error", 1);
        return result;
    }

    // CRC校验
    QByteArray dataPart = buf.left(buf.size()-2);
    quint16 receivedCrc = static_cast<quint8>(buf.at(buf.size()-2)) |
                          (static_cast<quint8>(buf.at(buf.size()-1)) << 8);
    if(calculateCRC(dataPart) != receivedCrc)
    {
        result.insert("error", 1);
        return result;
    }

    // 基础字段解析
    quint16 address = static_cast<quint8>(buf.at(0));
    quint16 funcCodeH = static_cast<quint8>(buf.at(2));
    quint16 funcCodeL = static_cast<quint8>(buf.at(3));
    quint16 funcCode = funcCodeH | funcCodeL;
    int dataLen = static_cast<quint8>(buf.at(4));
    result = procCommand(dataLen, funcCode, dataPart);
    result.insert("address", address);
    result.insert("funcCode", funcCode);

    return result;
}
QVariantMap BMSProtocol::procCommand(int dataLen, quint16 cmd, const QByteArray &data)
{
    auto it = commands.find(cmd);
    if (it != commands.end())
    {
        return it.value()(data, dataLen); // 调用绑定的成员函数
    }
    return {{"error", 2}};
}
QVariantMap BMSProtocol::parse(const QByteArray &buf, int &size, int &result)
{
    QVariantMap mp = {};
    return mp;
}

QVariantMap BMSProtocol::deal_14(const QByteArray &data, int dataLen)
{
    QVariantMap response;
    // 解析 data 并处理...
    quint8 SOH = static_cast<quint8>(data[5]);
    quint8 SOC = static_cast<quint8>(data[6]);
    // QString msg1 = QString("%1%").arg(SOH );
    // QString msg2 = QString("%1%").arg(SOC );
    response["SOH"] = SOH;
    response["SOC"] = SOC;
    return response;
}

QVariantMap BMSProtocol::deal_04(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    // 数据完整性校验
    if (dataLen != 4 || v.size() < 9)// v至少需要包含：地址(1)+功能码(1)+地址（2）+长度(1)+数据(4)
    {
        response["error"] = "Invalid data length";
        return response;
    }
    // 提取数据部分的4字节（大端序）
    quint32 rawValue = (static_cast<quint8>(v[5]) << 24) |  // 00
                       (static_cast<quint8>(v[6]) << 16) |  // 01
                       (static_cast<quint8>(v[7]) << 8)  |  // 37
                       static_cast<quint8>(v[8]);          // 20

    // 计算电呀值（假设单位为mV，需根据设备协议调整比例）
    double current_V = rawValue / 1000.0;

    response["electYa"] = QString::number(current_V, 'f', 3) + " V";
    return response;
}

QVariantMap BMSProtocol::deal_06(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    // 数据完整性校验
    if (dataLen != 4 || v.size() < 9)// v至少需要包含：地址(1)+功能码(1)+地址（2）+长度(1)+数据(4)
    {
        response["error"] = "Invalid data length";
        return response;
    }
    // 提取数据部分的4字节（大端序）
    quint32 rawValue = (static_cast<quint8>(v[5]) << 24) |  // 00
                       (static_cast<quint8>(v[6]) << 16) |  // 01
                       (static_cast<quint8>(v[7]) << 8)  |  // 37
                       static_cast<quint8>(v[8]);          // 20

    // 计算电流值（假设单位为mA，需根据设备协议调整比例）
    double current_A = rawValue / 1000.0;  // 转换为安培

    response["electLiu"] = QString::number(current_A, 'f', 3) + " A";
    return response;
}

QVariantMap BMSProtocol::deal_08(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    if (dataLen != 4 || v.size() < 9)
    {
        response["error"] = "Invalid data length";
        return response;
    }
    quint32 rawValue = (static_cast<quint8>(v[5]) << 24) |  // 00
                       (static_cast<quint8>(v[6]) << 16) |  // 01
                       (static_cast<quint8>(v[7]) << 8)  |  // 37
                       static_cast<quint8>(v[8]);          // 20
    response["capacity"] = rawValue;
    return response;
}

QVariantMap BMSProtocol::deal_0A(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    quint32 balStatus = (static_cast<quint8>(v[5]) << 24) |  // 00
                        (static_cast<quint8>(v[6]) << 16) |  // 01
                        (static_cast<quint8>(v[7]) << 8)  |  // 37
                        static_cast<quint8>(v[8]);          // 20
    response["balStatus"] = balStatus;
    return response;
}

QVariantMap BMSProtocol::deal_0C(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    int fangStatus = static_cast<quint8>(v[7]) & 1;
    int chongStatus = static_cast<quint8>(v[7]) & 2;
    response["fMos"] = fangStatus;
    response["cMos"] = chongStatus;

    return response;
}



QVariantMap BMSProtocol::deal_19(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    quint8 afeNum = static_cast<quint8>(v[5]);
    quint8 cusNum = static_cast<quint8>(v[6]);
    response["afeNum"] = afeNum;
    response["cusNum"] = cusNum;
    return response;
}

QVariantMap BMSProtocol::deal_1A(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    return response;
}

QVariantMap BMSProtocol::deal_1B(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    return response;
}
// 寄存器地址0x0000 - MOS温度1 (Uint16, 单位: 开尔文)
QVariantMap BMSProtocol::deal_00(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    // 数据校验：1个寄存器=2字节，v至少包含地址(1)+功能码(1)+长度(1)+数据(2)=5字节
    if (dataLen != 2 || v.size() < 5) {
        response["error"] = "数据长度错误";
        return response;
    }
    // 数据从v[5]开始：v[3]=起始地址高，v[4]=长度，v[5]=数据高，v[6]=数据低
    quint16 temp = (static_cast<quint8>(v[5]) << 8 | static_cast<quint8>(v[6]));
    response["mosTemp"] = QString::number(temp) + " K";
    return response;
}

// 寄存器地址0x0001 - 电池温度1 (Uint16, 单位: 开尔文)
QVariantMap BMSProtocol::deal_01(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    if (dataLen != 2 || v.size() < 5) {
        response["error"] = "Invalid data length";
        return response;
    }
    quint16 temp = (static_cast<quint8>(v[5]) << 8) | static_cast<quint8>(v[6]);
    response["cell_temp1"] = QString::number(temp) + " K";
    return response;
}
QVariantMap BMSProtocol::deal_02(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    if (dataLen != 2 || v.size() < 5) {
        response["error"] = "Invalid data length";
        return response;
    }
    quint16 temp = (static_cast<quint8>(v[5]) << 8) | static_cast<quint8>(v[6]);
    response["cell_temp2"] = QString::number(temp) + " K";
    return response;
}
QVariantMap BMSProtocol::deal_03(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    if (dataLen != 2 || v.size() < 5) {
        response["error"] = "Invalid data length";
        return response;
    }
    quint16 temp = (static_cast<quint8>(v[5]) << 8) | static_cast<quint8>(v[6]);
    response["cell_temp3"] = QString::number(temp) + " K";
    return response;
}
// 寄存器地址0x000E - 报警状态 (Uint16, 按位解析)
QVariantMap BMSProtocol::deal_0E(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    if (dataLen != 2 || v.size() < 5) {
        response["error"] = "Invalid data length";
        return response;
    }
    quint16 status = (static_cast<quint8>(v[5]) << 8) | static_cast<quint8>(v[6]);

    // 按位解析报警状态
    QVariantMap alarm;
    alarm["超高压报警"] = (status & 0x0001) ? "触发" : "正常";
    alarm["超低压报警"] = (status & 0x0002) ? "触发" : "正常";
    alarm["防拆卸报警"] = (status & 0x0004) ? "触发" : "正常";
    alarm["电压采集断线报警"] = (status & 0x0008) ? "触发" : "正常";
    alarm["温度采集断线报警"] = (status & 0x0010) ? "触发" : "正常";
    alarm["AFE通讯失效报警"] = (status & 0x0020) ? "触发" : "正常";
    alarm["电池组压差大报警"] = (status & 0x0040) ? "触发" : "正常";
    response["alarm_status"] = alarm;
    return response;
}

// 寄存器地址0x000F - 电池状态 (Uint16, 按位解析)
QVariantMap BMSProtocol::deal_0F(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    if (dataLen != 2 || v.size() < 5)
    {
        response["error"] = "Invalid data length";
        return response;
    }
    quint16 status = (static_cast<quint8>(v[5]) << 8) | static_cast<quint8>(v[6]);

    QVariantMap statusMap;
    statusMap["放电状态"] = (status & 0x0800) ? "放电中" : "未放电";
    statusMap["充电状态"] = (status & 0x1000) ? "充电中" : "未充电";
    statusMap["满充标志"] = (status & 0x0100) ? "已满充" : "未满充";
    // ... 其他位解析类似
    response["pack_status"] = statusMap;
    return response;
}

// 寄存器地址0x0020-0x003F - 单体电池电压 (Uint16, 单位: mV)
// 注：0x0021-0x003F的解析函数与deal_20逻辑相同，只需修改响应字段名称
QVariantMap BMSProtocol::deal_20(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    if (dataLen != 2 || v.size() < 5) {
        response["error"] = "Invalid data length";
        return response;
    }
    quint16 voltage = (static_cast<quint8>(v[3]) << 8) | static_cast<quint8>(v[4]);
    response["cell_voltage"] = QString::number(voltage) + " mV";
    return response;
}

// 0x0010 - 二次电压（单位：10mV）
QVariantMap BMSProtocol::deal_10(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    // 校验：1个寄存器返回2字节数据（v[4]=02 表示后续数据长度）
    if (dataLen != 2 || v.size() < 7) {
        response["error"] = "数据长度错误";
        return response;
    }

    // 组合数据（大端序）
    quint16 raw = (static_cast<quint8>(v[5]) << 8) | static_cast<quint8>(v[6]);
    double voltage = raw * 10.0;  // 转换为mV
    response["secondary_voltage"] = QString::number(voltage / 1000, 'f', 2) + " V";
    return response;
}

QVariantMap BMSProtocol::deal_11(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    return response;
}

QVariantMap BMSProtocol::deal_12(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    return response;
}

QVariantMap BMSProtocol::deal_13(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    return response;
}

// 0x0011 - 二次电流（单位：10mA，有符号）


// 0x0015 - RTC年份和月份（年份=值+2022）
QVariantMap BMSProtocol::deal_15(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    if (dataLen != 2 || v.size() < 7) {
        response["error"] = "数据长度错误";
        return response;
    }

    quint16 raw = (static_cast<quint8>(v[5]) << 8) | static_cast<quint8>(v[6]);
    quint16 year = (raw >> 8) + 2022;  // 高字节：年份偏移
    quint8 month = raw & 0xFF;         // 低字节：月份
    response["rtc_year"] = QString::number(year);
    response["rtc_month"] = QString::number(month);
    return response;
}

QVariantMap BMSProtocol::deal_16(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    return response;
}

QVariantMap BMSProtocol::deal_17(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    return response;
}

QVariantMap BMSProtocol::deal_18(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    return response;
}

// 0x001B - 满充容量（单位：10mAh，32位组合）


QVariantMap BMSProtocol::deal_1C(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    return response;
}

QVariantMap BMSProtocol::deal_1D(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    return response;
}

QVariantMap BMSProtocol::deal_1E(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    return response;
}

QVariantMap BMSProtocol::deal_1F(const QByteArray &v, int dataLen)
{
    QVariantMap response;
    return response;
}

// CRC16计算实现
quint16 BMSProtocol::calculateCRC(const QByteArray &data)
{
    quint16 crc = 0;
    for (char c : data)
    {
        crc = (crc << 8) ^ crc16tab[((crc >> 8) ^ (static_cast<quint8>(c))) & 0xFF];
    }
    return crc;
}

QVariant BMSProtocol::parseRegisterData(quint16 address, const QByteArray &data) const
{
    // 根据寄存器地址解析数据类型
    if(address >= 0x0000 && address <= 0x003F)
    { // 电压值
        quint16 value = static_cast<quint8>(data[0]) << 8 |
                        static_cast<quint8>(data[1]);
        return value; // 单位mV
    }
    else if(address == 0x0014) { // SOC/SOH
        QVariantMap socSoh;
        socSoh.insert("SOH", static_cast<quint8>(data[0]));
        socSoh.insert("SOC", static_cast<quint8>(data[1]));
        return socSoh;
    }
    // 添加其他数据类型解析...

    return QVariant();
}
