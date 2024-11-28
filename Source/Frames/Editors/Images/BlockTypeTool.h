//---------------------------------------------------------------------------
#ifndef BlockTypeToolH
#define BlockTypeToolH
//---------------------------------------------------------------------------
#include "Project/Documents/BaseImage.h"
#include "Visuals/GraphicsBuffer.h"
//---------------------------------------------------------------------------
class BlockTypeTool
{
private:
    Project::ImageDocument* m_ImageDocument;
   std::unique_ptr<TBitmap> m_CanvasBitmap;
   std::unique_ptr<TBitmap> m_BlendedBitmap;
    unsigned char           m_BlockType;
    String                  m_Blocks;
    int                     m_BlocksAcross;
    int                     m_BlocksDown;
    int                     m_BlockWidth;
    int                     m_BlockHeight;

    TPoint  __fastcall  PtToBlock(const TPoint& pt) const;
    void    __fastcall  Apply();

public:
            __fastcall  BlockTypeTool();

                        // return undo string
    String  __fastcall  Begin(Visuals::GraphicsBuffer& canvas);
                        // get the tool to do its thing
    char    __fastcall  Move(const TPoint& pt, const TShiftState& buttons);
                        // return redo string
    String  __fastcall  End();
    void    __fastcall  Draw(TBitmap* bitmap) const;

    __property  Project::ImageDocument*  Document  = { read = m_ImageDocument, write = m_ImageDocument };
    __property  unsigned char            BlockType = { read = m_BlockType    , write = m_BlockType     };
};
//---------------------------------------------------------------------------
#endif
