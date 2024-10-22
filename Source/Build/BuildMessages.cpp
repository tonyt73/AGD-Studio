//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "BuildMessages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall BuildMessages::BuildMessages()
: m_TreeView(nullptr)
, m_GroupNode(nullptr)
, m_MsgNode(nullptr)
{
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
    m_GroupType = type;
    m_GroupNode = m_TreeView->Items->Add(nullptr, group);
    m_GroupNode->ImageIndex = bmProgress;
    m_TreeView->Update();
}
//---------------------------------------------------------------------------
void __fastcall BuildMessages::Pop(bool result)
{
    m_GroupNode->ImageIndex = result ? m_GroupType : bmFailed;
    if (!result)
        m_GroupNode->Expand(false);
    m_TreeView->Update();
    m_GroupNode = nullptr;
}
//---------------------------------------------------------------------------
void __fastcall BuildMessages::Message(BuildMessageType type, const String& message)
{
	auto lines = System::Strutils::SplitString(message, "\n");
	for (auto line : lines) {
		auto node = m_TreeView->Items->AddChild(m_GroupNode, line);
		node->ImageIndex = type;
	}
	m_TreeView->Update();
}
//---------------------------------------------------------------------------
void __fastcall BuildMessages::Message(const String& message)
{
    m_MsgNode = m_TreeView->Items->AddChild(m_GroupNode, message);
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
