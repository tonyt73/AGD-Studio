//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "JumpTableDocument.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Project;
//---------------------------------------------------------------------------
__fastcall JumpTableDocument::JumpTableDocument(const String& name)
: Document(name)
{
    m_Type = "Jump";
    m_SubType = "Table";
    m_Extension = "json";
    m_Folder = "Game\\Configuration";
    m_File = GetFile();
    if (name != Unnamed)
    {
        m_PropertyMap["Steps[]"] = &m_Step;

        DefaultJumpTable();
    }
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
void __fastcall JumpTableDocument::OnLoaded()
{
    // set the default table if we loaded nothing
    DefaultJumpTable();
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
void __fastcall JumpTableDocument::DefaultJumpTable()
{
    if (m_Steps.size() == 0)
    {
        m_Steps.push_back(249);
        m_Steps.push_back(250);
        m_Steps.push_back(251);
        m_Steps.push_back(254);
        m_Steps.push_back(254);
        m_Steps.push_back(255);
        m_Steps.push_back(255);
        m_Steps.push_back(255);
        m_Steps.push_back(0);
        m_Steps.push_back(0);
        m_Steps.push_back(0);
        m_Steps.push_back(1);
        m_Steps.push_back(1);
        m_Steps.push_back(1);
        m_Steps.push_back(2);
        m_Steps.push_back(2);
        m_Steps.push_back(6);
        m_Steps.push_back(7);
        m_Steps.push_back(9);
        m_Steps.push_back(13);
        m_Steps.push_back(16);
        m_Steps.push_back(99);
    }
}
//---------------------------------------------------------------------------

