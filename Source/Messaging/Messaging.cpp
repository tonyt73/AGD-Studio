//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
unsigned int Bus::s_NextId = 0;
Bus::SubscriptionsMap* Bus::s_Handlers = nullptr;
//auto Bus::m_Handlers = new Bus::SubscriptionsMap();
//---------------------------------------------------------------------------
__fastcall ::Messaging::Registrar::Registrar()
{
}
//---------------------------------------------------------------------------
__fastcall ::Messaging::Registrar::~Registrar()
{
    Unsubscribe();
}
//---------------------------------------------------------------------------
// unsubscribe a handler from a message type
void ::Messaging::Bus::Unsubscribe(unsigned int subscriptionId)
{
    if (s_Handlers == nullptr)
        return;

    for (auto& subscriptions : *s_Handlers)
    {
        if (subscriptions.second != nullptr)
        {
            subscriptions.second->erase(std::remove_if(subscriptions.second->begin(), subscriptions.second->end(),
                [&](const std::unique_ptr<Subscription_>& sub) { return (subscriptionId == sub->SubscriptionId); }), subscriptions.second->end());
            if (subscriptions.second->size() == 0)
            {
                // remove the subscriptions from the handlers list
                s_Handlers->erase(subscriptions.first);
            }
        }
        else
        {
            s_Handlers->erase(subscriptions.first);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ::Messaging::Registrar::Unsubscribe()
{
    for (auto id : m_SubscriptionIds)
    {
        ::Messaging::Bus::Unsubscribe(id);
    }
    m_SubscriptionIds.clear();
}
//---------------------------------------------------------------------------

