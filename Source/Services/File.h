//---------------------------------------------------------------------------
#ifndef FileH
#define FileH
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
namespace Services
{
//---------------------------------------------------------------------------
class File
{
public:
    typedef ::System::TStringDynArray StrLines;
    static  bool    __fastcall  Exists(const String& file);
    static  String  __fastcall  NameWithoutExtension(const String& file);
    static  String  __fastcall  NameWithExtension(const String& file);
    static  String  __fastcall  Extension(const String& file);
    static  String  __fastcall  PathOf(const String& file);
    static  String  __fastcall  ChangeExtension(const String& filename, const String& extension);
    static  String  __fastcall  Cleanse(const String& file);
    static  String  __fastcall  Combine(const String& path, const String& filename);
    static  String  __fastcall  Resolve(const String& parent, const String& path);
    static  void    __fastcall  WriteText(const String& file, const String& content);
    static  void    __fastcall  PrependText(const String& file, const String& content);
    static  void    __fastcall  AppendText(const String& file, const String& content);
    static  String  __fastcall  ReadText(const String& file);
    static  void    __fastcall  ReadBytes(const String& file, std::vector<unsigned char>& contents);
    static StrLines __fastcall  ReadLines(const String& file);
    static  void    __fastcall  Copy(const String& source, const String& destination, bool overwrite = false);
    static  void    __fastcall  Delete(const String& file);
    static  void    __fastcall  Rename(const String& source, const String& destination);
};
//---------------------------------------------------------------------------
} // Services namespace
//---------------------------------------------------------------------------
#endif
