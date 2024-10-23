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
    TFrame*  m_ActiveEditor;

public:
             EditorManager();

    void     SetActive(TFrame* editor);
    bool     IsActive(const TFrame* editor) const;
};
//---------------------------------------------------------------------------
#define theEditorManager EditorManager::get()
//---------------------------------------------------------------------------
#endif
