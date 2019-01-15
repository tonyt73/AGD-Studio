//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Point.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace AGDX
{
//---------------------------------------------------------------------------
__fastcall Point::Point()
: System::Classes::TPersistent()
, m_X(0)
, m_Y(0)
{
}
//---------------------------------------------------------------------------
__fastcall Point::Point(int x, int y)
: System::Classes::TPersistent()
, m_X(x)
, m_Y(y)
{
}
//---------------------------------------------------------------------------
const Point& __fastcall Point::operator=(const Point& other)
{
    m_X = other.X;
    m_Y = other.Y;
    return *this;
}
//---------------------------------------------------------------------------
}