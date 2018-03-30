//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void ThemeSettings::ReapplyStyle()
{
	// force a change back to the current style to reapply it for a hidden form on activation
	auto style = TStyleManager::ActiveStyle->Name;
	TStyleManager::SetStyle(style == TStyleManager::StyleNames[0] ? TStyleManager::StyleNames[1] : TStyleManager::StyleNames[0]);
	TStyleManager::SetStyle(style);
}
//---------------------------------------------------------------------------
