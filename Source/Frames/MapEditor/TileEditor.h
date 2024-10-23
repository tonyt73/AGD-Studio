//---------------------------------------------------------------------------
#ifndef TileEditorH
#define TileEditorH
//---------------------------------------------------------------------------
#include "MapPencilTool.h"
#include "MapLineTool.h"
#include "MapRectTool.h"
#include "Project/TiledMapDocument.h"
#include "Messaging/Messaging.h"
#include "Messaging/Event.h"
#include "Visuals/Image.h"
#include "Visuals/GraphicsMode.h"
//---------------------------------------------------------------------------
class TileEditor
{
public:
    enum TEMode { temSelect, temPencil, temLine, temRect };
private:
    struct TFPoint
    {
        TFPoint() {}
        TFPoint(float x, float y) : x(x), y(y) {}
        float x;
        float y;
    };

    enum MouseModes { mmTool, mmGroupSelect };
    enum EntityDrawFilters { edfDirty = 1, edfSelected = 2, edfFirstTile = 4, edfForce = 8 };

    Registrar      m_Registrar;        // the messaging registrar
    std::unique_ptr<TBitmap>    m_Content;          // 1:1 content
    std::unique_ptr<TBitmap>    m_Tile0Content;     // 1:1 content with all tile0's used to clear the m_Content quickly
    TSize                       m_ContentSize;      // the size of the content window that we need (content bitmap is always larger for blt reasons)
    TImage* const               m_View;             // the UI image we render to
    TImage*                     m_LockIcon;         // the lock icon
    Project::MapEntityList      m_Entities;         // all the map entities
    Project::MapEntityList      m_ToolEntities;     // the entities for the current tool (select etc)
    Project::MapEntityList      m_ClipboardEntities;// the entities for the clipboard (copy, cut, paste)
    Project::MapEntity          m_ToolEntity;       // the image document selected in the map editor UI
    Project::MapEntity          m_HoverEntity;      // the entity the mouse is hovering over
    TEMode                      m_Mode;             // tool mode (pencil, line etc)
    bool                        m_Dirty;            // flag: tool is dirty - map needs updating
   const Visuals::GraphicsMode& m_GraphicsMode;     // the graphics mode used by the project
    Visuals::ImageMap&          m_ImageMap;         // a map of all images as bitmaps
    float                       m_ScaleFactor;      // the scale factor of the content view on to the overlays view
    TFPoint                     m_Scale;            // the applied scale factor for both x and y axes
    bool                        m_UsesGridTile;     // flag: uses a tile grid
    bool                        m_UsesGridRoom;     // flag: uses a room grid
    bool                        m_ShowGridTile;     // flag: show tile grid
    bool                        m_ShowGridRoom;     // flag: show room grid
    bool                        m_MousePanning;     // flag: panning the window with the mouse
    bool                        m_SelectionMove;    // flag: moving the entity selections
    bool                        m_ForceMapDraw;     // flag: force a full redraw of the map
    TPoint                      m_MapOffsetMS;      // offset into the map to render to the workspace (Coords in Map Space)
    TRect                       m_Window;           // the number of tiles across and down of the window area
    TSize                       m_TileSize;         // the size in pixels of a tile
    TSize                       m_Rooms;            // the number of rooms across and down
    TSize                       m_SelectedRoom;     // the currently selected room
    MouseModes                  m_MouseMode;        // the current state of mouse use (tool use or group select)
    MouseModes                  m_PrevMouseMode;    // tbe previous state of mouse use
    TPoint                      m_LastMouse;        // the last position of the mouse
    TPoint                      m_MoveMouse;        // the current position of the mouse
    TPoint                      m_GroupSelectSrtMS; // start group select pt (Coords in Map Space)
    TPoint                      m_GroupSelectEndMS; // end group select pt (Coords in Map Space)
    TPoint                      m_BorderScaled;     // the view border scaled to map space
    int                         m_Border;           // the size of a border around the tiles
    int                         m_SelectionCount;   // the number of entities selected
    unsigned int                m_Tile0Id;          // tile 0 id
    bool                        m_ReadOnly;         // read only - no changes allowed - room selection only
    bool                        m_ShowSelectedRoom; // show the selected room highlighted
    bool                        m_ShowStartRoom;    // show the start room highlighted
    bool                        m_ShowRoomNumbers;  // show room index numbers
    bool                        m_ShowTileTypes;    // show the tile types using their image editor colours
    bool                        m_ShowSpriteTypes;  // show the sprite type
    TPoint                      m_StartRoom;        // the location of the start room
    MapPencilTool               m_MapPencilTool;    // pencil tool - plot single entites
    MapRectTool                 m_MapRectTool;      // rect tool - draw tiles (only) in a rectangle
    MapLineTool                 m_MapLineTool;      // line tool - draw tiles (only) in a line
    MapTool*                    m_ActiveMapTool;    // the active tool (from 1 of 3 above)

    void                        OnWindowChanged(const WindowChangedEvent& event);
    void                        CreateViewBitmap();
    void                        Clear();
    void                        SelectRoom(TSize room);
    void                        ValidatePosition();
    TPoint                      MapToView(const TPoint& pt) const;
    TPoint                      ViewToMap(int X, int Y) const;
    void                        ResetToOrigin(Project::MapEntityList& list, const TPoint& originPt) const;
    bool                        GetGridTile();
    bool                        GetGridRoom();
    unsigned int                GetToolEntity() const;
    void                        SetGridTile(bool value);
    void                        SetGridRoom(bool value);
    void                        SetRooms(TSize rooms);
    void                        SetTile0Id(unsigned int id);
    void                        SetToolEntity(unsigned int id);
    void                        SetReadOnly(bool state);
    void                        SetShowSelectedRoom(bool state);
    void                        SetShowStartRoom(bool state);
    void                        SetShowRoomNumbers(bool state);
    void                        SetShowTileTypes(bool state);
    void                        SetShowSpriteTypes(bool state);
    void                        SetStartRoomCoords(TPoint location);
    void                        SetScale(float scale);
    void                        SetMode(TEMode mode);
    void                        SetLockIcon(TImage* icon);
    void                        DrawEntities(int filters, Visuals::ImageTypes type = Visuals::itInvalid);
    void                        DrawToolEntities();
    void                        DrawHoverEntity();
    void                        DrawMap();
    void                        DrawGrids() const;
    void                        DrawRoomNumbers() const;
    void                        DrawSpriteTypes() const;
    void                        DrawEntityLocks() const;
    void                        DrawGroupSelect() const;
    void                        DrawSelectedRoom() const;
    void                        DrawStartRoom() const;
    int                         Snap(int value, int range) const;
    void                        Get(const TRect& rect, Project::MapEntityList& entities) const;
    void                        ReplaceEntities();
    void                        UpdateTile0Content();
    bool                        ClearHover();
    void                        SelectHover();
    bool                        GetEntityUnderMouse(int X, int Y, Project::MapEntity& entity, Visuals::ImageTypes imageType, bool selectIt = false);
    void                        AssignRoomIndexes(Project::MapEntityList& entities);

    void             OnMouseDownSelectMode(TMouseButton Button, TShiftState Shift, int X, int Y);
    void             OnMouseDownMapToolMode(TMouseButton Button, TShiftState Shift, int X, int Y);
    void             OnMouseMoveSelectMode(TShiftState Shift, int X, int Y);
    void             OnMouseMoveMapToolMode(TShiftState Shift, int X, int Y);
    void             OnMouseUpSelectMode(TMouseButton Button, TShiftState Shift, int X, int Y);
    void             OnMouseUpMapToolMode(TMouseButton Button, TShiftState Shift, int X, int Y);

    __property  bool            IsDirty = { read = m_Dirty, write = m_Dirty };

    typedef void (__closure *TNotifyOnEntityClick)(const Project::MapEntity& entity);
    TNotifyOnEntityClick        FOnEntitySelected;
    typedef int (__closure *TRetrieveRoomIndex)(const TPoint& pt, bool newIndex) const;
    TRetrieveRoomIndex          FRetrieveRoomIndex;

public:

                                TileEditor(TImage* const view, Visuals::ImageMap& imageMap, const TSize& rooms, bool usesGridTile, bool usesGridRoom, int border, bool readOnly = false);
                               ~TileEditor();

    void                        OnMouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
    void                        OnMouseMove(TShiftState Shift, int X, int Y);
    void                        OnMouseUp(TMouseButton Button, TShiftState Shift, int X, int Y);

    void                        Refresh();
    void                        UpdateMap();

    void                        SetEntities(const Project::MapEntityList& entities);
  const Project::MapEntityList& GetEntities() const;
    void                        Add(const Project::MapEntityList& entities);
    void                        ToggleEntityLocks();
    void                        SetSpriteType(int type);
    Project::MapEntityList      GetSelection(bool resetToOrigin = false) const;
    void                        DeleteSelection();
    void                        UnselectAll(bool update = true);
    void                        Copy();
    void                        Cut();
    void                        Paste();

    // properties
    __property  TEMode          Mode                = { read = m_Mode            , write = SetMode            };
    __property  TSize           Rooms               = { write = SetRooms                                      };
    __property  float           Scale               = { read = m_ScaleFactor     , write = SetScale           };
    __property  bool            GridTile            = { read = m_ShowGridTile    , write = SetGridTile        };
    __property  bool            GridRoom            = { read = m_ShowGridRoom    , write = SetGridRoom        };
    __property  unsigned int    Tile0Id             = { read = m_Tile0Id         , write = SetTile0Id         };
    __property  unsigned int    ToolEntity          = { read = GetToolEntity     , write = SetToolEntity      };
    __property  bool            ReadOnly            = { read = m_ReadOnly        , write = SetReadOnly        };
    __property  TSize           SelectedRoom        = { read = m_SelectedRoom                                 };
    __property  TPoint          StartRoom           = { read = m_StartRoom       , write = SetStartRoomCoords };
    __property  bool            ShowSelectedRoom    = { read = m_ShowSelectedRoom, write = SetShowSelectedRoom};
    __property  bool            ShowStartRoom       = { read = m_ShowStartRoom   , write = SetShowStartRoom   };
    __property  bool            ShowRoomNumbers     = { read = m_ShowRoomNumbers , write = SetShowRoomNumbers };
    __property  bool            ShowTileTypes       = { read = m_ShowTileTypes   , write = SetShowTileTypes   };
    __property  bool            ShowSpriteTypes     = { read = m_ShowSpriteTypes , write = SetShowSpriteTypes };
    __property  TImage*         LockIcon            = { write = SetLockIcon                                   };

    // event handlers
    __property TNotifyOnEntityClick OnEntitySelected= { read = FOnEntitySelected , write = FOnEntitySelected  };
    __property TRetrieveRoomIndex  RetrieveRoomIndex= { read = FRetrieveRoomIndex, write = FRetrieveRoomIndex };
};
//---------------------------------------------------------------------------
#endif
