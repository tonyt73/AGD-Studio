//---------------------------------------------------------------------------
#ifndef BuildMessagesH
#define BuildMessagesH
//---------------------------------------------------------------------------
#include "ElXTree.hpp"
//---------------------------------------------------------------------------
enum BuildMessageType { bmOk, bmFailed, bmFolder };
//---------------------------------------------------------------------------
class BuildMessages
{
private:
    TElXTree*                   m_TreeView;

public:
                    __fastcall  BuildMessages();
    virtual         __fastcall ~BuildMessages();

                                // clear the tree view
        void        __fastcall  Clear();
                                // push a new group/folder node
        void        __fastcall  Push(const String& group);
                                // pop the last node
        void        __fastcall  Pop();
                                // post a message in the current group node
        void        __fastcall  Message(BuildMessageType type, const String& message);

    __property  TElXTree*       TreeView = { write = m_TreeView };
};
//---------------------------------------------------------------------------
#define BUILD_MSG_CLEAR() m_BuildMessages.Clear()
#define BUILD_MSG_PUSH(group) m_BuildMessages.Push(group)
#define BUILD_MSG(type, msg) m_BuildMessages.Message(type, msg)
#define BUILD_MSG_POP() m_BuildMessages.Pop()
//---------------------------------------------------------------------------
#endif
