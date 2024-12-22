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
            unsigned char           m_Step;

            void        __fastcall  DoSave() override;
            void        __fastcall  OnEndObject(const String& object) override;
            void        __fastcall  OnLoading() override;
            void        __fastcall  OnLoaded() override;
            int         __fastcall  GetStepCount() const;
            void        __fastcall  DefaultJumpTable();

public:
                        __fastcall  JumpTableDocument(const String& name);

    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new JumpTableDocument(name); }
    unsigned char       __fastcall  RawStep(int index) const;
    int                 __fastcall  GetStep(int index) const;
    void                __fastcall  SetStep(int index, int value);

    int                 __property  Count = { read = GetStepCount };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
