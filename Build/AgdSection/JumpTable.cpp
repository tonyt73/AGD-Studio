//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "JumpTable.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SectionBuilders::JumpTable::JumpTable()
: SectionBuilder("Jump Table")
{
    m_Steps[ 0] =   0;
    m_Steps[ 1] = -15;
    m_Steps[ 2] = -12;
    m_Steps[ 3] =  -9;
    m_Steps[ 4] =  -4;
    m_Steps[ 5] =  -4;
    m_Steps[ 6] =  -2;
    m_Steps[ 7] =  -2;
    m_Steps[ 8] =  -2;
    m_Steps[ 9] =   0;
    m_Steps[10] =   0;
    m_Steps[11] =   0;
    m_Steps[12] =   2;
    m_Steps[13] =   2;
    m_Steps[14] =   2;
    m_Steps[15] =   4;
    m_Steps[16] =   4;
    m_Steps[17] =   8;
    m_Steps[18] =  12;
    m_Steps[19] =  16;
    m_Steps[20] =  16;
    m_Steps[21] =  16;
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::JumpTable::~JumpTable()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::JumpTable::Execute()
{
#if 0
    String def = "DEFINEJUMP ";
    for (auto i = 1; i <= 21; i++)
    {
        if (m_Steps[i] < 0)
        {
            def += IntToStr(256 + m_Steps[i]);
        }
        else
        {
            def += IntToStr(m_Steps[i]);
        }
        def += " ";
    }
    def += "99";
#else
    // foggy jump table
    String def = "DEFINEJUMP 249 250 251 254 254 255 255 255 0 0 0 1 1 1 2 2 6 7 6 15 16 99";
#endif
    AddLine(def);
    LineBreak();

    Success();
}
//---------------------------------------------------------------------------

