//---------------------------------------------------------------------------
#pragma hdrstop
#include "Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#if defined(_WIN32) || defined(__APPLE__) || defined(__linux__)
auto ::Messaging::Bus::m_Handlers = new ::Messaging::Bus::SubscriptionsMap();
#endif // defined(_WIN32) || defined(__APPLE__) || defined(__linux__)
//---------------------------------------------------------------------------
