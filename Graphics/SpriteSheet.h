//---------------------------------------------------------------------------
#ifndef SpriteSheetH
#define SpriteSheetH
//---------------------------------------------------------------------------
#include <System.UITypes.hpp>
//---------------------------------------------------------------------------
#include <memory>
#include <vector>
//---------------------------------------------------------------------------
#include "Palette.h"
//---------------------------------------------------------------------------
namespace Graphics
{
//---------------------------------------------------------------------------
enum SpriteWays { swAll, swLeftRight, swUpDown };
//---------------------------------------------------------------------------
class SpriteSheet
{
private:
    String                      m_Name;
    String                      m_Description;
    int                         m_Width;
    int                         m_Height;
    int                         m_Ways;
    SpriteWays                  m_Direction;
    int                         m_Frames;
    bool                        m_HasShadow;
    std::unique_ptr<TBitmap>    m_SpriteSheet;
    std::unique_ptr<TBitmap>    m_ShadowSheet;
static std::unique_ptr<TBitmap> m_Checkerboard;
    std::unique_ptr<TBitmap>    m_View;
    std::unique_ptr<TBitmap>    m_Background;

    int         __fastcall      GetLayoutIndex() const;
    TSize       __fastcall      GetLayoutSize() const;
    bool        __fastcall      ParseFilename(const String& pngFile);
    static void __fastcall      InitialiseLayouts();

public:
                __fastcall      SpriteSheet();

                                // draw a specific frame to the bitmap
    void        __fastcall      Draw(TBitmap* bitmap, int way, int frame, float x, float y);
                                // draw all frames into layout formation
    TBitmap*    __fastcall      LayoutView(int frame, bool loop);
                                // load the bitmap from the file and set its definition parameters
    bool        __fastcall      Load(const String& pngFile);

    __property  String          Name = { read = m_Name };
    __property  String          Description = { read = m_Description };
    __property  int             Width = { read = m_Width };
    __property  int             Height = { read = m_Height };
    __property  int             Ways = { read = m_Ways };
    __property  int             Frames = { read = m_Frames };
};
//---------------------------------------------------------------------------
} // graphics namespace
//---------------------------------------------------------------------------
#endif
