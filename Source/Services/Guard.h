//---------------------------------------------------------------------------
#ifndef GuardH
#define GuardH
//---------------------------------------------------------------------------
namespace Services
{
//---------------------------------------------------------------------------
// A guard to use in a single function
// Sets the supplied guard flag to true while the function is running
// Check the flag in other functions to stop processing.
// Generally used when the UI is updating and you don't want to trigger
// and more control updates
//---------------------------------------------------------------------------
class Guard
{
private:
    bool&   m_Flag;
public:
            Guard(bool& flag);
           ~Guard();
};
//---------------------------------------------------------------------------
} // Services namespace
//---------------------------------------------------------------------------
#define GUARD(x) auto g = Services::Guard(x)
//---------------------------------------------------------------------------
#endif
