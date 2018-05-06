#ifndef CRC16_H
#define CRC16_H

#include <stddef.h>


typedef struct {
    unsigned short poly;
    unsigned short value;
    int refin;
    int refout;
    unsigned short xorout;
} CRC16;


#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#define CRC16_EXPORT __declspec(dllexport)
#else
#define CRC16_EXPORT
#endif


extern CRC16_EXPORT CRC16 CRC16_ARC;
extern CRC16_EXPORT CRC16 CRC16_AUT_CCITT;
extern CRC16_EXPORT CRC16 CRC16_BUYPASS;
extern CRC16_EXPORT CRC16 CRC16_CCITT_FALSE;
extern CRC16_EXPORT CRC16 CRC16_CDMA2000;
extern CRC16_EXPORT CRC16 CRC16_CMS;
extern CRC16_EXPORT CRC16 CRC16_DDS_110;
extern CRC16_EXPORT CRC16 CRC16_DECT_R;
extern CRC16_EXPORT CRC16 CRC16_DECT_X;
extern CRC16_EXPORT CRC16 CRC16_DNP;
extern CRC16_EXPORT CRC16 CRC16_EN_13753;
extern CRC16_EXPORT CRC16 CRC16_GENIBUS;
extern CRC16_EXPORT CRC16 CRC16_GSM;
extern CRC16_EXPORT CRC16 CRC16_LJ1200;
extern CRC16_EXPORT CRC16 CRC16_MAXIM;
extern CRC16_EXPORT CRC16 CRC16_MCRF4XX;
extern CRC16_EXPORT CRC16 CRC16_OPENSAFETY_A;
extern CRC16_EXPORT CRC16 CRC16_OPENSAFETY_B;
extern CRC16_EXPORT CRC16 CRC16_PROFIBUS;
extern CRC16_EXPORT CRC16 CRC16_RIELLO;
extern CRC16_EXPORT CRC16 CRC16_T10_DIF;
extern CRC16_EXPORT CRC16 CRC16_TELEDISK;
extern CRC16_EXPORT CRC16 CRC16_TMS37157;
extern CRC16_EXPORT CRC16 CRC16_USB;
extern CRC16_EXPORT CRC16 CRC16_CRC_A;
extern CRC16_EXPORT CRC16 CRC16_KERMIT;
extern CRC16_EXPORT CRC16 CRC16_MODBUS;
extern CRC16_EXPORT CRC16 CRC16_X_25;
extern CRC16_EXPORT CRC16 CRC16_XMODEM;


CRC16_EXPORT CRC16 *crc16_new(
    CRC16 *self,
    unsigned short poly,
    unsigned short value,
    int refin,
    int refout,
    unsigned short xorout
);

CRC16_EXPORT CRC16 *crc16_load(
    CRC16 *self,
    CRC16 algorithm
);

CRC16_EXPORT void crc16_update(
    CRC16 *self,
    const void *data,
    size_t length
);

CRC16_EXPORT unsigned short crc16_digest(
    CRC16 *self
);

CRC16_EXPORT unsigned short crc16_algorithm_digest(
    CRC16 algorithm,
    const void *data,
    size_t length
);


#ifdef __cplusplus
}
#endif


#endif

