//---------------------------------------------------------------------------
#ifndef PointH
#define PointH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
namespace AGDX
{
class Point : public System::Classes::TPersistent
{
private:
    int m_X;
    int m_Y;

public:
                    __fastcall  Point();
                    __fastcall  Point(int x, int y);

    const Point&    __fastcall  operator=(const Point& other);

__published:
    __property  int X = { read = m_X, write = m_X, default = 0 };
    __property  int Y = { read = m_Y, write = m_Y, default = 0 };
};
}
//---------------------------------------------------------------------------
#endif
