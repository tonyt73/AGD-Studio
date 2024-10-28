//---------------------------------------------------------------------------
#ifndef EditorManagerH
#define EditorManagerH
//---------------------------------------------------------------------------
#include "fEditor.h"
//---------------------------------------------------------------------------
class EditorManager
{
public: // singleton
    static EditorManager& get();
    EditorManager(EditorManager const&) = delete;
    void operator=(EditorManager const&) = delete;

private:
    TfrmEditor*         m_ActiveEditor;

public:
            __fastcall  EditorManager();

    void    __fastcall  SetActive(TfrmEditor* editor);
    bool    __fastcall  IsActive(const TfrmEditor* editor) const;
};
//---------------------------------------------------------------------------
#define theEditorManager EditorManager::get()
//---------------------------------------------------------------------------
#endif
