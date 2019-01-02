//---------------------------------------------------------------------------
#ifndef MapToolH
#define MapToolH
//---------------------------------------------------------------------------
#include "Project/MapDocuments.h"
#include "System/Generic.h"
#include "Frames/Tool.h"
//---------------------------------------------------------------------------
class MapTool : public Tool
{
private:
    TSize                       m_TileSize;     // the size in pixels of a tile

protected:
                                // draw functions
            int     __fastcall  Snap(int value, int range) const;
            void    __fastcall  SnapToTileGrid(TPoint& pt) const;
            void    __fastcall  SnapToTileGrid(TRect& rect) const;
    virtual void    __fastcall  Apply(EntityList& list, Entity entity, TPoint pt) = 0;
            void    __fastcall  Set(EntityList& list, const Entity& entity);

    __property  TSize           TileSize = { read = m_TileSize };

public:
                    __fastcall  MapTool();
    virtual         __fastcall ~MapTool();

                                // return undo string
            String  __fastcall  Begin(EntityList& list, Entity entity, const TPoint& pt, const TShiftState& buttons);
                                // get the tool to do its thing
            void    __fastcall  Move(EntityList& list, Entity entity, const TPoint& pt, const TShiftState& buttons);
                                // return redo string
            String  __fastcall  End(EntityList& list, Entity entity, const TPoint& pt);
};
//---------------------------------------------------------------------------
#endif
