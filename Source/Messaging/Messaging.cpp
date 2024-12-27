//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
unsigned int Bus::s_NextId = 0;
Bus::SubscriptionsMap* Bus::s_Handlers = nullptr;
//auto Bus::m_Handlers = new Bus::SubscriptionsMap();
//---------------------------------------------------------------------------
Registrar::Registrar()
{
}
//---------------------------------------------------------------------------
Registrar::~Registrar()
{
    Unsubscribe();
}
//---------------------------------------------------------------------------
Bus::Subscription_::Subscription_(unsigned int id)
: m_SubscriptionId(id)
{
}
//---------------------------------------------------------------------------
Bus::Subscription_::~Subscription_()
{
}
//---------------------------------------------------------------------------
// unsubscribe a handler from a message type
void Bus::Unsubscribe(unsigned int subscriptionId)
{
    if (s_Handlers) {
        for (auto& subscriptions : *s_Handlers) {
            if (subscriptions.second) {
                subscriptions.second->erase(std::remove_if(subscriptions.second->begin(), subscriptions.second->end(),
                    [&](const std::unique_ptr<Subscription_>& sub) {
                    return (subscriptionId == sub->SubscriptionId);
                }), subscriptions.second->end());
                if (subscriptions.second->size() == 0) {
                    // remove the subscriptions from the handlers list
                    s_Handlers->erase(subscriptions.first);
                return;
                }
            } else {
                s_Handlers->erase(subscriptions.first);
                return;
            }
        }
    }
}
//---------------------------------------------------------------------------
void Registrar::Unsubscribe()
{
    for (auto id : m_SubscriptionIds) {
        Bus::Unsubscribe(id);
    }
    m_SubscriptionIds.clear();
}
//---------------------------------------------------------------------------

