//---------------------------------------------------------------------------
#ifndef JumpTableDocumentH
#define JumpTableDocumentH
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

            void         DoSave();
            void         OnEndObject(const String& object);
            void         OnLoading();
            void         OnLoaded();
            int          GetStepCount() const;
            void         DefaultJumpTable();

public:
                         JumpTableDocument(const String& name);

    static  Document*    Create(const String& name, const String& extra) { return new JumpTableDocument(name); };
    unsigned char        RawStep(int index) const;
    int                  GetStep(int index) const;
    void                 SetStep(int index, int value);

    int                 __property  Count = { read = GetStepCount };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
