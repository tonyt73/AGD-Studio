//---------------------------------------------------------------------------
#ifndef ImageH
#define ImageH
//---------------------------------------------------------------------------
#include <memory>
#include "Graphics/GraphicsBuffers.h"
//---------------------------------------------------------------------------
class Image : public System::JsonFile
{
private:
        std::unique_ptr<GraphicsBuffer> m_GraphicsBuffer;
public:
        virtual     __fastcall  Image(unsigned int width, unsigned int height, const GraphicsMode& graphicsMode);
            void    __fastcall  SetPixel(unsigned int X, unsigned int Y, unsigned char color);
};
//---------------------------------------------------------------------------
#endif
