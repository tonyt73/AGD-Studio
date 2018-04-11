//---------------------------------------------------------------------------
#ifndef SnapshotH
#define SnapshotH
//---------------------------------------------------------------------------
// Z80      little endian
// 6502     little endian
// 68K      big endian
// Intel    big endian
enum CpuEndianness { LittleEndian, BigEndian };
//---------------------------------------------------------------------------
class Snapshot
{
protected:
    struct Locations
    {
        unsigned int    Font;
        unsigned int    Map;
        unsigned int    Window;
        unsigned int    NumberOfScreens;
        unsigned int    Pointers;
        unsigned int    PointersA;
        unsigned int    PointersB;
        unsigned int    StartScreenA;
        unsigned int    StartScreenB;
        unsigned int    StuffToSkip;
    };

    std::vector<unsigned char>  m_Memory;
    CpuEndianness               m_Endianness;           // defaults to little endian
    unsigned char               m_Version;              // AGD Version
    String                      m_Snapshoter;           // the class managing the snapshot
    String                      m_Errors;               // List of errors when loading/validating the snapshot
    Locations                   m_Locations;
    unsigned int                m_SnapshotSize;         // the required size of the snapshot


            void    __fastcall  Error(const String& error);

public:
                    __fastcall  Snapshot(CpuEndianness endianness, unsigned int snapshotSize);

    virtual bool    __fastcall  Load(const String& file);

            UInt8   __fastcall  Byte(unsigned int address) const;
            UInt16  __fastcall  Word(unsigned int address) const;

    CpuEndianness   __property  Endianness = { read = m_Endianness };
    unsigned char   __property  Version = { read = m_Version };
    String          __property  Errors = { read = m_Errors };
    Locations       __property  Location = { read = m_Locations };
};
//---------------------------------------------------------------------------
class ZXSpectrum48KSnapshot : public Snapshot
{
public:
                    __fastcall  ZXSpectrum48KSnapshot();
};
//---------------------------------------------------------------------------
class AmstradCPCSnapshot : public Snapshot
{
public:
                    __fastcall  AmstradCPCSnapshot();
};
//---------------------------------------------------------------------------
// TODO: Amstrad CPC snapshot
//---------------------------------------------------------------------------
#endif
