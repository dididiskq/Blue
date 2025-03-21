#include "hmutils.h"
#include "hmcrc.h"




CHMCrc::CHMCrc()
{

}


CHMCrc::~CHMCrc()
{

}

QByteArray CHMCrc::getCalcCRC(const QByteArray &a)
{
    QByteArray tmp = a;
    ushort bcc = CalcCRC(tmp.data(), tmp.size());
    return getDataLen(bcc);
}

QByteArray CHMCrc::getCalcCRC32(const QByteArray &a)
{
    QByteArray tmp = a;
    uint bcc = CalculateCrc32((unsigned char*)tmp.data(), tmp.size());
    return _getDataLen(bcc);
}

unsigned short CHMCrc::CalcCRC(char *data, int size)
{

    int i;
    unsigned short crc = 0;
    for (i = 0; i < size; i++) {
        crc = CRC(crc, data[i]);
    }
    return crc;
}

unsigned int CHMCrc::_CalcCRC(char *data, int size)
{
    int i;
    unsigned int crc = 0;
    for (i = 0; i < size; i++) {
        crc = CRC(crc, data[i]);
    }
    return crc;
}

QByteArray CHMCrc::getDataLen(ushort len)
{
    QByteArray arr;
    char l = len&0x00ff;
    arr.append(l);
    char h = (len&0xff00) >> 8;
    arr.append(h);
    return arr;
}

QByteArray CHMCrc::_getDataLen(uint len)
{
    QByteArray arr;
    char l = len&0x00ff;
    arr.append(l);
    char h = (len&0xff00) >> 8;
    arr.append(h);
    char ll = (len&0x00ff0000) >> 16;
    arr.append(ll);
    char hh = (len&0xff000000) >> 24;
    arr.append(hh);
    return arr;
}

unsigned long CHMCrc::CalculateCrc32(unsigned char *data_p, unsigned short length)	//Calculate CRC32
{
   unsigned long crc32 = static_cast<unsigned long>(-1);
   unsigned char *pS = (unsigned char*)data_p;
   while (length--)
   {
      crc32 = crc32_tab[(*pS++ ^ (unsigned char) crc32)] ^ (crc32 >> 8);
   }
   return (crc32)^ 0xffffffff;
}


