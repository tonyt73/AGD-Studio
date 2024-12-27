//---------------------------------------------------------------------------
#ifndef GenericH
#define GenericH
//---------------------------------------------------------------------------
namespace Services
{
//---------------------------------------------------------------------------
class Generic
{
private:
    typedef std::map<String, String> StringMap;
    String      m_Object;
    StringMap   m_Objects;

    void        Process();

public:
                Generic();
                Generic(const String& object);

    void        Add(const String& name, const String& value);
    void        Add(const String& name, const bool& value);
    void        Add(const String& name, const int& value);
    void        Add(const String& name, const float& value);

    bool        Get(const String& name, String& value);
    bool        Get(const String& name, bool& value);
    bool        Get(const String& name, int& value);
    bool        Get(const String& name, float& value);

    template <class T>
    T           Get(const String& name)
                    {
                        T value;
                        Get(name, value);
                        return value;
                    }

    String      Get() const;
};
//---------------------------------------------------------------------------
} // Services namespace
//---------------------------------------------------------------------------
#endif
