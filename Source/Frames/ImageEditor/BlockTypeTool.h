//---------------------------------------------------------------------------
#ifndef BlockTypeToolH
#define BlockTypeToolH
//---------------------------------------------------------------------------
#include "Project/ImageDocument.h"
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

    TPoint                  PtToBlock(const TPoint& pt) const;
    void                    Apply();

public:
                            BlockTypeTool();

                            // return undo string
    String                  Begin(Visuals::GraphicsBuffer& canvas);
                            // get the tool to do its thing
    char                    Move(const TPoint& pt, const TShiftState& buttons);
                            // return redo string
    String                  End();
    void                    Draw(TBitmap* bitmap) const;

    __property  Project::ImageDocument*  Document  = { read = m_ImageDocument, write = m_ImageDocument };
    __property  unsigned char            BlockType = { read = m_BlockType    , write = m_BlockType     };
};
//---------------------------------------------------------------------------
#endif
