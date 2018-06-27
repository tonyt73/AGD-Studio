//---------------------------------------------------------------------------
#ifndef ImportAgdFileH
#define ImportAgdFileH
//---------------------------------------------------------------------------
#include "ImportFile.h"
//---------------------------------------------------------------------------
class ImportAgdFile : public ImportFile
{
private:
    String  __fastcall  PreProcess(const String& data) const;
    void    __fastcall  Convert(const String& data);
    void    __fastcall  ConvertScreen(const String& data);
    void    __fastcall  ConvertMap(const String& data);
    void    __fastcall  ConvertWindow(const String& data);
    void    __fastcall  ConvertBlock(const String& data);
    void    __fastcall  ConvertObject(const String& data);
    void    __fastcall  ConvertSprite(const String& data);
    void    __fastcall  ConvertFont(const String& data);
    void    __fastcall  ConvertMessages(const String& data);

public:
            __fastcall  ImportAgdFile();

    bool    __fastcall  Process(const String& file);
};
//---------------------------------------------------------------------------
#endif
