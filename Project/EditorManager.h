//---------------------------------------------------------------------------
#ifndef EditorManagerH
#define EditorManagerH
//---------------------------------------------------------------------------
class EditorManager
{
public: // singleton
    static EditorManager& get();
    EditorManager(EditorManager const&) = delete;
    void operator=(EditorManager const&) = delete;

private:
    TFrame*             m_ActiveEditor;

public:
            __fastcall  EditorManager();

    void    __fastcall  SetActive(TFrame* editor);
    bool    __fastcall  IsEditorActive(TFrame* editor) const;
};
//---------------------------------------------------------------------------
#define theEditorManager EditorManager::get()
//---------------------------------------------------------------------------
#endif
