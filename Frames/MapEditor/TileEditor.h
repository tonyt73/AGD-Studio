//---------------------------------------------------------------------------
#ifndef TileEditorH
#define TileEditorH
//---------------------------------------------------------------------------
#include "Project/MapDocuments.h"
#include "Graphics/Image.h"
#include "Graphics/GraphicsMode.h"
//---------------------------------------------------------------------------
class TileEditor
{
public:
    enum TEMode { temSelect, temPencil, temLine, temShape };
private:
    enum MouseModes { mmTool, mmMove, mmGroupSelect };
    enum EntityDrawFilters { edfDirty = 1, edfSelected = 2, edfFirstTile = 4, edfForce = 8 };

    std::unique_ptr<TBitmap>        m_Content;      // 1:1 content
    std::unique_ptr<TBitmap>        m_Tile0Window;
    TImage* const                   m_View;
    EntityList                      m_Entities;
    EntityList                      m_ToolEntities;
    Agdx::ImageMap                  m_ImageMap;
    TEMode                          m_Mode;
    bool                            m_Dirty;
    const Agdx::GraphicsMode&       m_GraphicsMode; // the graphics mode used by the project
    int                             m_Scale;        // the scale factor of the content view on to the overlays view
    bool                            m_UsesGridTile; // flag: uses a tile grid
    bool                            m_UsesGridRoom; // flag: uses a room grid
    bool                            m_ShowGridTile; // flag: show tile grid
    bool                            m_ShowGridRoom; // flag: show room grid
    bool                            m_MousePanning; // flag: panning the window with the mouse
    bool                            m_SelectionMove;// flag: moving the entity selections
    bool                            m_ForceMapDraw; // flag: force a full redraw of the map
    TPoint                          m_Position;     // offset into the view to render the workspace
    TSize                           m_Size;         // the number of tiles across and down of the area
    TSize                           m_TileSize;     // the size in pixels of a tile
    MouseModes                      m_MouseMode;
    MouseModes                      m_PrevMouseMode;
    TPoint                          m_LastMouse;
    TPoint                          m_MoveMouse;
    TPoint                          m_GroupSelectS; // start group select pt
    TPoint                          m_GroupSelectE; // end group select pt
    int                             m_Border;       // the size of a border around the tiles
    int                             m_SelectionCount;
    unsigned int                    m_Tile0Id;      // tile 0 id

    void                __fastcall  OnEvent(const Event& event);
    void                __fastcall  Clear();
    void                __fastcall  ValidatePosition();
    TPoint              __fastcall  GetCursorPt(int X, int Y) const;
    bool                __fastcall  GetGridTile();
    bool                __fastcall  GetGridRoom();
    void                __fastcall  SetGridTile(bool value);
    void                __fastcall  SetGridRoom(bool value);
    void                __fastcall  SetSize(TSize size);
    void                __fastcall  SetTile0Id(unsigned int id);
    void                __fastcall  UpdateMap();
    void                __fastcall  RefreshImages();
    void                __fastcall  DrawEntities(int filters);
    void                __fastcall  DrawMap();
    void                __fastcall  DrawGrids() const;
    void                __fastcall  DrawGroupSelect() const;
    void                __fastcall  UnselectAll();

    __property  bool                IsDirty = { read = m_Dirty, write = m_Dirty };

    void                __fastcall  Get(const TRect& rect, EntityList& entities) const;
    void                __fastcall  Add(EntityList& entities);
    void                __fastcall  Remove(const TRect& rect);

public:

                        __fastcall  TileEditor(TImage* const view, const TSize& size, bool usesGridTile, bool usesGridRoom, int border);
                        __fastcall ~TileEditor();

    void                __fastcall  OnMouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
    void                __fastcall  OnMouseMove(TShiftState Shift, int X, int Y);
    void                __fastcall  OnMouseUp(TMouseButton Button, TShiftState Shift, int X, int Y);

    void                __fastcall  Refresh();

    void                __fastcall  SetEntities(const EntityList& entities);
    const EntityList&   __fastcall  GetEntities() const  ;

    __property  TEMode              Mode = { read = m_Mode, write = m_Mode };
    __property  TSize               Size = { write = SetSize };
    __property  unsigned int        Scale = { read = m_Scale, write = m_Scale };
    __property  bool                GridTile = { read = m_ShowGridTile, write = SetGridTile };
    __property  bool                GridRoom = { read = m_ShowGridRoom, write = SetGridRoom };
    __property  unsigned int        Tile0Id = { read = m_Tile0Id, write = SetTile0Id };
};
//---------------------------------------------------------------------------
#endif
