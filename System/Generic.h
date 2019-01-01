//---------------------------------------------------------------------------
#ifndef GenericH
#define GenericH
//---------------------------------------------------------------------------
#include <map>
//---------------------------------------------------------------------------
class Generic
{
private:
	String              		m_Object;
	std::map<String, String>    m_Objects;

	void  	__fastcall  Process();

public:
			__fastcall 	Generic();
			__fastcall 	Generic(const String& object);
			__fastcall 	Generic(const Generic& other);

	void    __fastcall  Add(const String& name, const String& value);
	void    __fastcall  Add(const String& name, const bool& value);
	void    __fastcall  Add(const String& name, const int& value);
	void    __fastcall  Add(const String& name, const float& value);

	bool    __fastcall  Get(const String& name, String& value);
	bool    __fastcall  Get(const String& name, bool& value);
	bool    __fastcall  Get(const String& name, int& value);
	bool    __fastcall  Get(const String& name, float& value);

    template <class T>
	T       __fastcall  Get(const String& name)
                        {
                            T value;
                            Get(name, value);
                            return value;
                        }

    String  __fastcall  Get() const;
};
//---------------------------------------------------------------------------
#endif
