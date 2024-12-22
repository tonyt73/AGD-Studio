//---------------------------------------------------------------------------
#ifndef FileH
#define FileH
//---------------------------------------------------------------------------
namespace Services
{
//---------------------------------------------------------------------------
class File
{
public:
    typedef System::TStringDynArray StrLines;
    static  bool      Exists(const String& file);
    static  String    NameWithoutExtension(const String& file);
    static  String    NameWithExtension(const String& file);
    static  String    Extension(const String& file);
    static  String    PathOf(const String& file);
    static  String    ChangeExtension(const String& filename, const String& extension);
    static  String    Cleanse(const String& file);
    static  String    Combine(const String& path, const String& filename);
    static  String    Resolve(const String& parent, const String& path);
    static  void      WriteText(const String& file, const String& content);
    static  void      PrependText(const String& file, const String& content);
    static  void      AppendText(const String& file, const String& content);
    static  String    ReadText(const String& file);
    static  void      ReadBytes(const String& file, std::vector<wchar_t>& contents);
    static  StrLines  ReadLines(const String& file);
    static  void      Copy(const String& source, const String& destination, bool overwrite = false);
    static  void      Delete(const String& file);
    static  void      Rename(const String& source, const String& destination);
};
//---------------------------------------------------------------------------
} // Services namespace
//---------------------------------------------------------------------------
#endif
