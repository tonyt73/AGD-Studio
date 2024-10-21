//---------------------------------------------------------------------------
#ifndef CharacterSetDocumentH
#define CharacterSetDocumentH
//---------------------------------------------------------------------------
#include "ImageDocument.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class CharacterSetDocument : public ImageDocument
{
private:
public:
						        __fastcall  CharacterSetDocument(const String& name, const String& extra);
	static  Project::Document*  __fastcall  Create(const String& name, const String& extra) { return new CharacterSetDocument(name, extra); };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
