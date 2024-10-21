//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "Guard.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Services;
//---------------------------------------------------------------------------
__fastcall Guard::Guard(bool& flag)
: m_Flag(flag)
{
	m_Flag = true;
}
//---------------------------------------------------------------------------
__fastcall Guard::~Guard()
{
	m_Flag = false;
}
//---------------------------------------------------------------------------
