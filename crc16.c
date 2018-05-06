#include "crc16.h"


/* CRC-16/ARC */
CRC16_EXPORT CRC16 CRC16_ARC             = {0x8005, 0x0000, 1, 1, 0x0000};

/* CRC-16/AUG-CCITT */
CRC16_EXPORT CRC16 CRC16_AUT_CCITT       = {0x1021, 0x1d0f, 0, 0, 0x0000};

/* CRC-16/BUYPASS */
CRC16_EXPORT CRC16 CRC16_BUYPASS         = {0x8005, 0x0000, 0, 0, 0x0000};

/* CRC-16/CCITT-FALSE */
CRC16_EXPORT CRC16 CRC16_CCITT_FALSE     = {0x1021, 0xffff, 0, 0, 0x0000};

/* CRC-16/CDMA2000 */
CRC16_EXPORT CRC16 CRC16_CDMA2000        = {0xc867, 0xffff, 0, 0, 0x0000};

/* CRC-16/CMS */
CRC16_EXPORT CRC16 CRC16_CMS             = {0x8005, 0xffff, 0, 0, 0x0000};

/* CRC-16/DDS-110 */
CRC16_EXPORT CRC16 CRC16_DDS_110         = {0x8005, 0x800d, 0, 0, 0x0000};

/* CRC-16/DECT-R */
CRC16_EXPORT CRC16 CRC16_DECT_R          = {0x0589, 0x0000, 0, 0, 0x0001};

/* CRC-16/DECT-X */
CRC16_EXPORT CRC16 CRC16_DECT_X          = {0x0589, 0x0000, 0, 0, 0x0000};

/* CRC-16/DNP */
CRC16_EXPORT CRC16 CRC16_DNP             = {0x3d65, 0x0000, 1, 1, 0xffff};

/* CRC-16/EN-13757 */
CRC16_EXPORT CRC16 CRC16_EN_13753        = {0x3d65, 0x0000, 0, 0, 0xffff};

/* CRC-16/GENIBUS */
CRC16_EXPORT CRC16 CRC16_GENIBUS         = {0x1021, 0xffff, 0, 0, 0xffff};

/* CRC-16/GSM */
CRC16_EXPORT CRC16 CRC16_GSM             = {0x1021, 0x0000, 0, 0, 0xffff};

/* CRC-16/LJ1200 */
CRC16_EXPORT CRC16 CRC16_LJ1200          = {0x6f63, 0x0000, 0, 0, 0x0000};

/* CRC-16/MAXIM */
CRC16_EXPORT CRC16 CRC16_MAXIM           = {0x8005, 0x0000, 1, 1, 0xffff};

/* CRC-16/MCRF4XX */
CRC16_EXPORT CRC16 CRC16_MCRF4XX         = {0x1021, 0xffff, 1, 1, 0x0000};

/* CRC-16/OPENSAFETY-A */
CRC16_EXPORT CRC16 CRC16_OPENSAFETY_A    = {0x5935, 0x0000, 0, 0, 0x0000};

/* CRC-16/OPENSAFETY-B */
CRC16_EXPORT CRC16 CRC16_OPENSAFETY_B    = {0x755b, 0x0000, 0, 0, 0x0000};

/* CRC-16/PROFIBUS */
CRC16_EXPORT CRC16 CRC16_PROFIBUS        = {0x1dcf, 0xffff, 0, 0, 0xffff};

/* CRC-16/RIELLO (0xb2aa reversed) */
CRC16_EXPORT CRC16 CRC16_RIELLO          = {0x1021, 0x554d, 1, 1, 0x0000};

/* CRC-16/T10-DIF */
CRC16_EXPORT CRC16 CRC16_T10_DIF         = {0x8bb7, 0x0000, 0, 0, 0x0000};

/* CRC-16/TELEDISK */
CRC16_EXPORT CRC16 CRC16_TELEDISK        = {0xa097, 0x0000, 0, 0, 0x0000};

/* CRC-16/TMS37157 (0x89ec reversed) */
CRC16_EXPORT CRC16 CRC16_TMS37157        = {0x1021, 0x3791, 1, 1, 0x0000};

/* CRC-16/USB */
CRC16_EXPORT CRC16 CRC16_USB             = {0x8005, 0xffff, 1, 1, 0xffff};

/* CRC-A (0xc6c6 reversed) */
CRC16_EXPORT CRC16 CRC16_CRC_A           = {0x1021, 0x6363, 1, 1, 0x0000};

/* KERMIT */
CRC16_EXPORT CRC16 CRC16_KERMIT          = {0x1021, 0x0000, 1, 1, 0x0000};

/* MODBUS */
CRC16_EXPORT CRC16 CRC16_MODBUS          = {0x8005, 0xffff, 1, 1, 0x0000};

/* X-25 */
CRC16_EXPORT CRC16 CRC16_X_25            = {0x1021, 0xffff, 1, 1, 0xffff};

/* XMODEM */
CRC16_EXPORT CRC16 CRC16_XMODEM          = {0x1021, 0x0000, 0, 0, 0x0000};


static unsigned short crc16_reflect(unsigned short n, int length) {
    unsigned short r = 0;
    int i;
    for(i = 0; i < length; i++)
        r |= ((n >> i) & 1) << (length - i - 1);
    return r;
}


CRC16_EXPORT CRC16 *crc16_new(
    CRC16 *self,
    unsigned short poly,
    unsigned short value,
    int refin,
    int refout,
    unsigned short xorout
) {
    if(!self)
        return 0;
    self->poly = poly;
    self->value = value;
    self->refin = refin;
    self->refout = refout;
    self->xorout = xorout;
    if(self->refin)
        self->value = crc16_reflect(self->value, 16);
    return self;
}


CRC16_EXPORT CRC16 *crc16_load(CRC16 *self, CRC16 algorithm) {
    return crc16_new(
        self,
        algorithm.poly,
        algorithm.value,
        algorithm.refin,
        algorithm.refout,
        algorithm.xorout
    );
}


CRC16_EXPORT void crc16_update(CRC16 *self, const void *data, size_t length) {
    if(self) {
        size_t i, j;
        const unsigned char *x = (const unsigned char *)data;
        for(i = 0; i < length; i++) {
            self->value ^= self->refin ? crc16_reflect(x[i], 8) : x[i] << 8;
            for(j = 0; j < 8; j++) {
                if(self->value & 0x8000)
                    self->value = (self->value << 1) ^ self->poly;
                else
                    self->value <<= 1;
            }
        }
    }
}


CRC16_EXPORT unsigned short crc16_digest(CRC16 *self) {
    if(self) {
        unsigned short digest = self->value;
        if(self->refout)
            digest = crc16_reflect(digest, 16);
        return digest ^ self->xorout;
    }
    return 0;
}


CRC16_EXPORT unsigned short crc16_algorithm_digest(
    CRC16 algorithm,
    const void *data, size_t length
) {
    CRC16 self;
    crc16_load(&self, algorithm);
    crc16_update(&self, data, length);
    return crc16_digest(&self);
}
