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
template <class T>
class OnImport : public Event
{
private:
    T m_Value;
public:
    __fastcall OnImport(const String& id, const T& value)
    : Event(id)
    , m_Value(value)
    {
    }

    __property  T Value = { read = m_Value };
};
//---------------------------------------------------------------------------
class OnImportWindow : public Event
{
private:
     TPoint m_Location;
     TSize  m_Size;
public:
    __fastcall OnImportWindow(const TPoint& location, const TSize& size)
    : Event("Window")
    , m_Location(location)
    , m_Size(size)
    {
    }

    __property  TPoint  Location = { read = m_Location };
    __property  TSize   Size     = { read = m_Size     };
};
//---------------------------------------------------------------------------
#endif
