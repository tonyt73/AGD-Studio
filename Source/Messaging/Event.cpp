//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "Event.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
template class ::Messaging::OnChange<int>;
template class ::Messaging::OnChange<float>;
template class ::Messaging::OnChange<String>;
template class ::Messaging::OnChange<bool>;
template class ::Messaging::DocumentChange<String>;
//---------------------------------------------------------------------------

