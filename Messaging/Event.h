//---------------------------------------------------------------------------
#ifndef EventH
#define EventH
//---------------------------------------------------------------------------
class Event
{
private:
    String  m_Id;
public:
            __fastcall  Event(const String& id) : m_Id(id) {}

    __property  String  Id = { read = m_Id };
};
//---------------------------------------------------------------------------
template <class T>
class OnChange : public Event
{
private:
    T m_Value;
public:
    __fastcall OnChange(const String& id, const T& value)
    : Event(id)
    , m_Value(value)
    {
    }

    __property  T Value = { read = m_Value };
};
//---------------------------------------------------------------------------
enum ErrorType { etInformation, etWarning, etError, etDebug, etHelpKeys };
class OnMessage : public Event
{
private:
    ErrorType   m_ErrorType;
public:
    __fastcall OnMessage(const String& message, ErrorType type)
    : Event(message)
    , m_ErrorType(type)
    {
    }

    __property  String      Message = { read = m_Id };
    __property  ErrorType   Type    = { read = m_ErrorType };
};
//---------------------------------------------------------------------------
class ErrorMessage : public OnMessage
{
private:

public:
    __fastcall ErrorMessage(const String& message)
    : OnMessage(message, etError)
    {
    }
};
//---------------------------------------------------------------------------
class WarningMessage : public OnMessage
{
private:

public:
    __fastcall WarningMessage(const String& message)
    : OnMessage(message, etWarning)
    {
    }
};
//---------------------------------------------------------------------------
class InformationMessage : public OnMessage
{
private:

public:
    __fastcall InformationMessage(const String& message)
    : OnMessage(message, etInformation)
    {
    }
};
//---------------------------------------------------------------------------
class DebugMessage : public OnMessage
{
private:

public:
    __fastcall DebugMessage(const String& message)
    : OnMessage(message, etDebug)
    {
    }
};
//---------------------------------------------------------------------------
class HelpKeysMessage : public OnMessage
{
private:

public:
    __fastcall HelpKeysMessage(const String& message)
    : OnMessage(message, etHelpKeys)
    {
    }
};
//---------------------------------------------------------------------------
class OnMapResized : public Event
{
private:
    unsigned int m_Width;
    unsigned int m_Height;

public:
    __fastcall OnMapResized(unsigned int width, unsigned int height)
    : Event("MapResized")
    , m_Width(width)
    , m_Height(height)
    {
    }

    __property  unsigned int Width = { read = m_Width, write = m_Width };
    __property  unsigned int Height = { read = m_Height, write = m_Height };
};
//---------------------------------------------------------------------------
#endif
