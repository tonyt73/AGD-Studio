//---------------------------------------------------------------------------
#ifndef crc32cH
#define crc32cH
//---------------------------------------------------------------------------
// https://stackoverflow.com/questions/27939882/fast-crc-algorithm
//---------------------------------------------------------------------------
/* CRC-32C (iSCSI) polynomial in reversed bit order. */
#define POLY 0x82f63b78
/* CRC-32 (Ethernet, ZIP, etc.) polynomial in reversed bit order. */
/* #define POLY 0xedb88320 */
//---------------------------------------------------------------------------
class crc32c {
public:
    static uint32_t calc(const wchar_t *buf, size_t len, uint32_t crc = 0);
};
//---------------------------------------------------------------------------
#endif
