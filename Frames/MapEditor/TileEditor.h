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
    struct TFPoint
    {
        TFPoint() {}
        TFPoint(float x, float y) : x(x), y(y) {}
        float x;
        float y;
    };

    enum MouseModes { mmTool, mmMove, mmGroupSelect };
    enum EntityDrawFilters { edfDirty = 1, edfSelected = 2, edfFirstTile = 4, edfForce = 8 };

    std::unique_ptr<TBitmap>        m_Content;      	// 1:1 content
	std::unique_ptr<TBitmap>        m_Tile0Window;      // a bitmap containing a full screen of tile 0's (usually the blank tile)
    TSize                           m_ContentSize;      // the size of the content window that we need (content bitmap is always larger for blt reasons)
	TImage* const                   m_View;             // the UI image we render to
	EntityList                      m_Entities;         // all the map entities
	EntityList                      m_ToolEntities;     // the entities for the current tool
	Agdx::ImageMap                  m_ImageMap;         // a rendering of each tile, object, sprite
	TEMode                          m_Mode;         	// tool mode (pencil, line etc)
	bool                            m_Dirty;            // flag: tool is dirty - map needs updating
	const Agdx::GraphicsMode&       m_GraphicsMode; 	// the graphics mode used by the project
    float                           m_ScaleFactor;      // the scale factor of the content view on to the overlays view
	TFPoint                         m_Scale;            // the applied scale factor for both x and y axes
	bool                            m_UsesGridTile; 	// flag: uses a tile grid
	bool                            m_UsesGridRoom; 	// flag: uses a room grid
	bool                            m_ShowGridTile; 	// flag: show tile grid
	bool                            m_ShowGridRoom; 	// flag: show room grid
	bool                            m_MousePanning; 	// flag: panning the window with the mouse
	bool                            m_SelectionMove;	// flag: moving the entity selections
	bool                            m_ForceMapDraw; 	// flag: force a full redraw of the map
	TPoint                          m_PositionMS;       // offset into the map to render to the workspace (Coords in Map Space)
	TSize                           m_WindowSize;       // the number of tiles across and down of the window area
	TSize                           m_TileSize;     	// the size in pixels of a tile
    TSize                           m_Rooms;            // the number of rooms across and down
	MouseModes                      m_MouseMode;        //
	MouseModes                      m_PrevMouseMode;    //
	TPoint                          m_LastMouse;        //
	TPoint                          m_MoveMouse;        //
	TPoint                          m_GroupSelectSrtMS; // start group select pt (Coords in Map Space)
	TPoint                          m_GroupSelectEndMS; // end group select pt (Coords in Map Space)
    TFPoint                         m_BorderScaled;     //
	int                             m_Border;       	// the size of a border around the tiles
	int                             m_SelectionCount;   // the number of entities selected
	unsigned int                    m_Tile0Id;      	// tile 0 id
	unsigned int                    m_SelectedEntity;	// selected entity id
    bool                            m_ReadOnly;         // read only - no changes allowed - room selection only

    void                __fastcall  CreateViewBitmap();
    void                __fastcall  OnEvent(const Event& event);
    void                __fastcall  Clear();
    void                __fastcall  ClearSelection();
    void                __fastcall  SelectRoom(TSize room);
    void                __fastcall  ValidatePosition();
    TPoint              __fastcall  MapToView(const TPoint& pt) const;
    TPoint              __fastcall  ViewToMap(int X, int Y) const;
    bool                __fastcall  GetGridTile();
    bool                __fastcall  GetGridRoom();
    void                __fastcall  SetGridTile(bool value);
    void                __fastcall  SetGridRoom(bool value);
    void                __fastcall  SetRooms(TSize rooms);
	void                __fastcall  SetTile0Id(unsigned int id);
	void                __fastcall  SetSelectedEntity(unsigned int id);
	void                __fastcall  SetReadOnly(bool state);
    void                __fastcall  SetScale(float scale);
    void                __fastcall  RefreshImages();
    void                __fastcall  DrawEntities(int filters);
    void                __fastcall  DrawMap();
    void                __fastcall  DrawGrids() const;
    void                __fastcall  DrawGroupSelect() const;
    int                 __fastcall  Snap(int value, int range);

    __property  bool                IsDirty = { read = m_Dirty, write = m_Dirty };

    void                __fastcall  Get(const TRect& rect, EntityList& entities) const;

public:

                        __fastcall  TileEditor(TImage* const view, const TSize& rooms, bool usesGridTile, bool usesGridRoom, int border, bool readOnly = false);
                        __fastcall ~TileEditor();

    void                __fastcall  OnMouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
    void                __fastcall  OnMouseMove(TShiftState Shift, int X, int Y);
    void                __fastcall  OnMouseUp(TMouseButton Button, TShiftState Shift, int X, int Y);

    void                __fastcall  Refresh();
    void                __fastcall  UpdateMap();

    void                __fastcall  SetEntities(const EntityList& entities);
    const EntityList&   __fastcall  GetEntities() const;
    void                __fastcall  Add(const EntityList& entities);
    EntityList          __fastcall  GetSelection() const;
    void                __fastcall  DeleteSelection();
    void                __fastcall  UnselectAll();

    __property  TEMode              Mode = { read = m_Mode, write = m_Mode };
    __property  TSize               Rooms = { write = SetRooms };
    __property  float               Scale = { read = m_ScaleFactor, write = SetScale };
    __property  bool                GridTile = { read = m_ShowGridTile, write = SetGridTile };
    __property  bool                GridRoom = { read = m_ShowGridRoom, write = SetGridRoom };
    __property  unsigned int        Tile0Id = { read = m_Tile0Id, write = SetTile0Id };
	__property  unsigned int        SelectedEntity = { read = m_SelectedEntity, write = SetSelectedEntity };
    __property  bool                ReadOnly = { read = m_ReadOnly, write = SetReadOnly };
};
//---------------------------------------------------------------------------
#endif
