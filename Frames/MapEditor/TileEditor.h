//---------------------------------------------------------------------------
#ifndef TileEditorH
#define TileEditorH
//---------------------------------------------------------------------------
#include "Graphics/GraphicsMode.h"
//---------------------------------------------------------------------------
class TileEditor
{
public:
    enum TEMode { temSelect, temPencil, temLine, temShape };
private:
    enum MouseModes { mmTool, mmMove };

    struct TAssetInfo
    {
        unsigned int x;
        unsigned int y;
        unsigned int id;
    } _ai;
    typedef std::vector<TAssetInfo> AssetList;

    std::unique_ptr<TBitmap>        m_Content;      // 1:1 content
    TImage* const                   m_View;
    AssetList                       m_Assets;
    AssetList                       m_ToolAssets;
    TEMode                          m_Mode;
    bool                            m_Dirty;
    const Agdx::GraphicsMode&       m_GraphicsMode; // the graphics mode used by the project
    int                             m_Scale;        // the scale factor of the content view on to the overlays view
    bool                            m_UsesGridTile; // flag: uses a tile grid
    bool                            m_UsesGridRoom; // flag: uses a room grid
    bool                            m_ShowGridTile; // flag: show tile grid
    bool                            m_ShowGridRoom; // flag: show room grid
    TPoint                          m_Position;     // offset into the view to render the workspace
    TSize                           m_Size;         // the number of tiles across and down of the area
    TSize                           m_TileSize;     // the size in pixels of a tile
    MouseModes                      m_MouseMode;
    TPoint                          m_LastMouse;
    int                             m_Border;       // the size of a border around the tiles

    void                __fastcall  Clear();
    void                __fastcall  ValidatePosition();
    void                __fastcall  DrawGrids();

    bool                __fastcall  GetGridTile();
    bool                __fastcall  GetGridRoom();
    void                __fastcall  SetGridTile(bool value);
    void                __fastcall  SetGridRoom(bool value);
    void                __fastcall  SetSize(TSize size);
    void                __fastcall  UpdateMap();

    __property  bool                IsDirty = { read = m_Dirty, write = m_Dirty };

public:

                        __fastcall  TileEditor(TImage* const view, const TSize& size, bool usesGridTile, bool usesGridRoom, int border);

    void                __fastcall  OnMouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
    void                __fastcall  OnMouseMove(TShiftState Shift, int X, int Y);
    void                __fastcall  OnMouseUp(TMouseButton Button, TShiftState Shift, int X, int Y);

    void                __fastcall  Refresh();

    __property  TEMode              Mode = { read = m_Mode, write = m_Mode };
    __property  TSize               Size = { write = SetSize };
    __property  unsigned int        Scale = { read = m_Scale, write = m_Scale };
    __property  bool                GridTile = { read = m_ShowGridTile, write = SetGridTile };
    __property  bool                GridRoom = { read = m_ShowGridRoom, write = SetGridRoom };
};
//---------------------------------------------------------------------------
#endif
