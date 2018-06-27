//---------------------------------------------------------------------------
#ifndef ImportFileH
#define ImportFileH
//---------------------------------------------------------------------------
class ImportFile
{
protected:
    String                      m_File;

            void    __fastcall  Error(const String& message) const;
            void    __fastcall  Warning(const String& message) const;
            void    __fastcall  Information(const String& message) const;
public:
                    __fastcall  ImportFile();
                    __fastcall ~ImportFile();

    virtual bool    __fastcall  Process(const String& file) = 0;
};
//---------------------------------------------------------------------------
#endif
