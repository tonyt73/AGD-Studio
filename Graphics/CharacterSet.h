//---------------------------------------------------------------------------
#ifndef CharacterSetH
#define CharacterSetH
//---------------------------------------------------------------------------
#include <fmx.h>
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class CharacterSet
{
private:
            String              m_File;
    std::unique_ptr<TBitmap>    m_Bitmap;

    String      __fastcall      GetName();

public:
                __fastcall      CharacterSet(const String& file);
                __fastcall     ~CharacterSet();

    TBitmap*    __fastcall      Bitmap();

    String      __property      Name = { read = GetName };
};
//---------------------------------------------------------------------------
} // project namepsace
//---------------------------------------------------------------------------
#endif
