//---------------------------------------------------------------------------
#ifndef JsonFileH
#define JsonFileH
//---------------------------------------------------------------------------
namespace Services
{
//---------------------------------------------------------------------------
// This class and it's descendants MUST BE instantiated dynamically using 'new'
//---------------------------------------------------------------------------
class JsonFile : public TPersistent
{
private:
    TStringWriter*              m_StringWriter;
    TJsonTextWriter*            m_JsonWriter;
    String                      m_File;

protected:
    // map member variables to property names
    // the loader will set the value based on the property type
    // TODO: Can we improve this to include the desired data type for safer conversion
    std::map<String, void*>     m_PropertyMap;

protected:
    void             Open(const String& file);
    void             Close();
    // write (on save)
    void             StartObject() const;
    void             EndObject() const;
    void             Push(const String& section) const;
    void             Pop() const;
    void             ArrayStart(const String& property) const;
    void             ArrayEnd() const;
    void             Write(const String& value) const;
    void             Write(const int& value) const;
    void             Write(const long& value) const;
    void             Write(const String& property, const String& value) const;
    void             Write(const String& property, const int& value) const;
    void             Write(const String& property, const unsigned int& value) const;
    void             Write(const String& property, const long& value) const;
    void             Write(const String& property, const float& value) const;
    void             Write(const String& property, const bool& value) const;
    // read (on load)
    virtual void     Set(const String& property, const String& value);
    virtual void     Set(const String& property, const int& value);
    virtual void     Set(const String& property, const unsigned int& value);
    virtual void     Set(const String& property, const long& value);
    virtual void     Set(const String& property, const float& value);
    virtual void     Set(const String& property, const bool& value);

            String   ProcessPath(const String& path) const;
    virtual void     Load(const String& file);

    virtual void     OnStartObject(const String& object);
    virtual void     OnEndObject(const String& object);

    virtual void     OnLoading();
    virtual void     OnLoaded();

public:
                     JsonFile();
    virtual         ~JsonFile();
};
//---------------------------------------------------------------------------
} // namespace Services
//---------------------------------------------------------------------------
#endif
