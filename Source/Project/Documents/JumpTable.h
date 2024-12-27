//---------------------------------------------------------------------------
#ifndef JumpTableH
#define JumpTableH
//---------------------------------------------------------------------------
#include "Document.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class JumpTableDocument : public Document
{
private:
    std::vector<unsigned char>      m_Steps;
    unsigned char                   m_Step;

    void                __fastcall  DoSave() override;
    void                __fastcall  OnEndObject(const String& object) override;
    void                __fastcall  OnLoading() override;
    void                __fastcall  OnLoaded() override;
    unsigned char       __fastcall  GetStepCount() const;
            void        __fastcall  DefaultJumpTable();

public:
                        __fastcall  JumpTableDocument(const String& name);

    static  Document*   __fastcall  Create(const String& name, const String&) { return new JumpTableDocument(name); }
    unsigned char       __fastcall  RawStep(unsigned char index) const;
    int                 __fastcall  GetStep(unsigned char index) const;
    void                __fastcall  SetStep(unsigned char index, int value);

    unsigned char       __property  Count = { read = GetStepCount };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
