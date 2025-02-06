//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "BuildMessages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall BuildMessages::BuildMessages()
: m_TreeView(nullptr)
, m_MsgNode(nullptr)
{
    m_GroupNodes.push_back(nullptr);
    m_GroupTypes.push_back(bmProgress);
}
//---------------------------------------------------------------------------
__fastcall BuildMessages::~BuildMessages()
{
}
//---------------------------------------------------------------------------
void __fastcall BuildMessages::Clear()
{
    m_TreeView->Items->Clear();
    m_TreeView->Update();
}
//---------------------------------------------------------------------------
void __fastcall BuildMessages::Push(BuildMessageType type, const String& group)
{
    m_GroupTypes.push_back(type);
    auto parentNode = m_GroupNodes.back();
    auto newNode = m_TreeView->Items->AddChild(parentNode, group);
    newNode->ImageIndex = bmProgress;
    m_GroupNodes.push_back(newNode);
    m_TreeView->Update();
}
//---------------------------------------------------------------------------
void __fastcall BuildMessages::Pop(bool expand)
{
    auto node = m_GroupNodes.back();
    node->ImageIndex = m_GroupTypes.back();
    if (expand) {
        node->Expand(true);
    }
    m_TreeView->Update();
    m_GroupTypes.pop_back();
    m_GroupNodes.pop_back();
}
//---------------------------------------------------------------------------
void __fastcall BuildMessages::Message(BuildMessageType type, const String& message)
{
    auto parentNode = m_GroupNodes.back();
    auto lines = SplitString(message, "\n");
    for (auto line : lines) {
        auto node = m_TreeView->Items->AddChild(parentNode, line);
        node->ImageIndex = type;
    }
    m_TreeView->Update();
}
//---------------------------------------------------------------------------
void __fastcall BuildMessages::Message(const String& message)
{
    auto parentNode = m_GroupNodes.back();
    m_MsgNode = m_TreeView->Items->AddChild(parentNode, message);
    m_MsgNode->ImageIndex = bmProgress;
    m_TreeView->Update();
}
//---------------------------------------------------------------------------
void __fastcall BuildMessages::Message(BuildMessageType type)
{
    m_MsgNode->ImageIndex = type;
    m_TreeView->Update();
}
//---------------------------------------------------------------------------
void __fastcall BuildMessages::Time(int time)
{
    Message(bmTiming, "Elapsed time: " + IntToStr(time) + "ms");
}
//---------------------------------------------------------------------------
