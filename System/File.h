//---------------------------------------------------------------------------
#ifndef FileH
#define FileH
//---------------------------------------------------------------------------
namespace System
{
//---------------------------------------------------------------------------
class File
{
public:
    static  bool    __fastcall  Exists(const String& file);
    static  String  __fastcall  NameWithoutExtension(const String& file);
    static  String  __fastcall  NameWithExtension(const String& file);
    static  String  __fastcall  PathOf(const String& file);
    static  String  __fastcall  ChangeExtension(const String& filename, const String& extension);
    static  String  __fastcall  Combine(const String& path, const String& filename);
    static  void    __fastcall  WriteText(const String& file, const String& content);
    static  String  __fastcall  ReadText(const String& file);
    static  void    __fastcall  Copy(const String& source, const String& destination);
    static  void    __fastcall  Delete(const String& file);
};
//---------------------------------------------------------------------------
} // filesystem namespace
//---------------------------------------------------------------------------
#endif
