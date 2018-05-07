//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "System/File.h"
//---------------------------------------------------------------------------
#include "Snapshot.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Snapshot::Snapshot(CpuEndianness endianness, unsigned int snapshotSize)
: m_Endianness(endianness)
, m_SnapshotSize(snapshotSize)
{
}
//---------------------------------------------------------------------------
bool __fastcall Snapshot::Load(const String& file)
{
    if (System::File::Exists(file))
    {
        System::File::ReadBytes(file, m_Memory);
        if (m_Memory.size() > 0)
        {
            if (m_Memory.size() == m_SnapshotSize)
            {
                auto address = Word(Location.PointersA);
                if (address == 36924)
                {
                    m_Version = 46;
                    Location.Pointers = Location.PointersA;
                }
                else
                {
                    m_Version = 47;
                    Location.Pointers = Location.PointersB;
                }
                return true;
            }
            Error("File: " + file + " is not a valid " + m_Snapshoter + " snapshot file");
            return false;
        }
        Error("File: " + file + " is empty");
        return false;
    }
    Error("File: " + file + " was not found");
    return false;
}
//---------------------------------------------------------------------------
void __fastcall Snapshot::Error(const String& error)
{
    m_Errors += "ERROR: " + error + "\r\n";
}
//---------------------------------------------------------------------------
UInt8 __fastcall Snapshot::Byte(unsigned int address) const
{
    return m_Memory[address];
}
//---------------------------------------------------------------------------
UInt16 __fastcall Snapshot::Word(unsigned int address) const
{
    auto b1 = m_Memory[address+0] << (m_Endianness == LittleEndian ? 0 : 8);
    auto b2 = m_Memory[address+1] << (m_Endianness == LittleEndian ? 8 : 4);
    return b1 + b2;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
const unsigned int ZX_48K_SNAPSHOT_SIZE = 49179;
//---------------------------------------------------------------------------
__fastcall ZXSpectrum48KSnapshot::ZXSpectrum48KSnapshot()
: Snapshot(LittleEndian, ZX_48K_SNAPSHOT_SIZE)
{
    m_Snapshoter = "ZX Spectrum 48K";
    m_Locations.Font = 31232 + 27 - 16384;
    m_Locations.Map = 31959 + 27 - 16384;
    m_Locations.Window = 32008 + 27 - 16384;
    m_Locations.NumberOfScreens = 32018 + 27 - 16384;
    m_Locations.Pointers = 32059 + 27 - 16384;
    m_Locations.PointersA = 32057 + 27 - 16384;
    m_Locations.PointersB = 32059 + 27 - 16384;
    m_Locations.StartScreenA = 33580 + 27 - 16384;
    m_Locations.StartScreenB = 33615 + 27 - 16384;
    m_Locations.StuffToSkip = 16384 - 27;
}
//---------------------------------------------------------------------------
const unsigned int ZX_128K_SNAPSHOT_SIZE = 49179;
//---------------------------------------------------------------------------
__fastcall ZXSpectrum128KSnapshot::ZXSpectrum128KSnapshot()
: Snapshot(LittleEndian, ZX_128K_SNAPSHOT_SIZE)
{
    m_Snapshoter = "ZX Spectrum 128K";
    // TODO: Add 128k snapshot addresses
    m_Locations.Font = 31232 + 27 - 16384;
    m_Locations.Map = 31959 + 27 - 16384;
    m_Locations.Window = 32008 + 27 - 16384;
    m_Locations.NumberOfScreens = 32018 + 27 - 16384;
    m_Locations.Pointers = 32059 + 27 - 16384;
    m_Locations.PointersA = 32057 + 27 - 16384;
    m_Locations.PointersB = 32059 + 27 - 16384;
    m_Locations.StartScreenA = 33580 + 27 - 16384;
    m_Locations.StartScreenB = 33615 + 27 - 16384;
    m_Locations.StuffToSkip = 16384 - 27;
}
//---------------------------------------------------------------------------
