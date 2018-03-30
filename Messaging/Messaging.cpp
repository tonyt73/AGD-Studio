//---------------------------------------------------------------------------
#pragma hdrstop
#include "Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#if defined(_WIN32) || defined(__APPLE__) || defined(__linux__)
auto ::Messaging::Bus::handlers = new ::Messaging::Bus::SubscriptionsMap();
#endif // defined(_WIN32) || defined(__APPLE__) || defined(__linux__)
//---------------------------------------------------------------------------
