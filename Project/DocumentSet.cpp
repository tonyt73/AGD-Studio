//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "DocumentSet.h"
#include "DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall DocumentSet::DocumentSet()
{
    m_MultiDoc = true;
}
//---------------------------------------------------------------------------
void __fastcall DocumentSet::Clear()
{
}
//---------------------------------------------------------------------------
Document* __fastcall DocumentSet::Add()
{
    return theDocumentManager.Add(m_Type, m_SubType, Name);
}
//---------------------------------------------------------------------------
void __fastcall DocumentSet::Remove(int index)
{
}
//---------------------------------------------------------------------------
void __fastcall DocumentSet::Remove(const String& name)
{
}
//---------------------------------------------------------------------------
Document* __fastcall DocumentSet::Get(int index)
{
    return nullptr;
}
//---------------------------------------------------------------------------
Document* __fastcall DocumentSet::Get(const String& name)
{
    return nullptr;
}
//---------------------------------------------------------------------------
int __fastcall DocumentSet::GetCount()
{
    return m_Documents.size();
}
//---------------------------------------------------------------------------
