//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Project/JumpTableDocument.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall JumpTableDocument::JumpTableDocument(const String& name)
: Document(name)
{
    m_Type = "Jump";
    m_SubType = "Table";
    m_Extension = "json";
    m_Folder = "Game\\Configuration";
    m_File = GetFile();
    m_PropertyMap["Steps[]"] = &m_Step;
}
//---------------------------------------------------------------------------
void __fastcall JumpTableDocument::DoSave()
{
    ArrayStart("Steps");
        for (auto step : m_Steps)
        {
            Write(step);
        }
    ArrayEnd();  // Steps
}
//---------------------------------------------------------------------------
void __fastcall JumpTableDocument::OnEndObject(const String& object)
{
    if (object == "Steps[]")
    {
        m_Steps.push_back(m_Step);
    }
}
//---------------------------------------------------------------------------
void __fastcall JumpTableDocument::OnLoading()
{
    m_Steps.clear();
}
//---------------------------------------------------------------------------
unsigned char __fastcall JumpTableDocument::RawStep(int index) const
{
    if (0 <= index && index < m_Steps.size() - 1)
    {
        return m_Steps[index];
    }
    return 0;
}
//---------------------------------------------------------------------------
int __fastcall JumpTableDocument::GetStep(int index) const
{
    if (0 <= index && index < m_Steps.size() - 1)
    {
        auto step = m_Steps[index];
        return step < 128 ? step : step - 256;
    }
    return 0;
}
//---------------------------------------------------------------------------
void __fastcall JumpTableDocument::SetStep(int index, int value)
{
    if (0 <= index && index < m_Steps.size() - 1)
    {
        value = std::max(-15, std::min(16, value));
        m_Steps[index] = value >= 0 ? value : value + 256;
    }
}
//---------------------------------------------------------------------------
int __fastcall JumpTableDocument::GetStepCount() const
{
    return m_Steps.size() - 1;
}
//---------------------------------------------------------------------------

