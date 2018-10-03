#include "basefun.h"

QString Convert(uint32_t u32Num)
{
    char szHex[11];
    sprintf(szHex,"0x%08X",u32Num);
    return QString(szHex);
}

QString Convert(uint64_t u64ByteSize)
{
    char szBuffer[50];
    uint8_t uLevel = 0;

    QString text;

    while(u64ByteSize > 1024){
        u64ByteSize /= 1024;
        uLevel++;
    }

    switch (uLevel) {
    case 0:
        szBuffer[0] = '\0';
        break;///bytes
    case 1:
        sprintf(szBuffer,"%liKB",u64ByteSize);
        break;///K
    case 2:
        sprintf(szBuffer,"%liMB",u64ByteSize);
        break;///M
    case 3:
        sprintf(szBuffer,"%liGB",u64ByteSize);
        break;///G
    default:
        szBuffer[0] = '\0';
        break;
    }

    text = QString(szBuffer);
    return text;
}
