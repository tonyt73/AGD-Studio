//---------------------------------------------------------------------------
#ifndef MessagingH
#define MessagingH
//---------------------------------------------------------------------------
#if defined(_WIN32) || defined(__APPLE__) || defined(__linux__)
#include <list>
#include <memory>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
//---------------------------------------------------------------------------
using namespace std;
namespace Messaging
{
class Bus
{
private:
    // Non-templated base class
    // Makes storing the templated objects easier
    class Subscription_
    {
    public:
        virtual ~Subscription_() {};
    };
    // Template specialization of a message subscription
    template <class T>
    class Subscription : public Subscription_
    {
    private:
        std::function<void (const T&)> handler;
    public:
        __fastcall Subscription(std::function<void (const T&)> handler)
        : handler(handler)
        {
        }
        __property std::function<void (const T&)> Handler = { read = handler };
    };

    // the map of message subscription handlers
    typedef std::list<std::unique_ptr<Subscription_>> Subscriptions;
    typedef std::unordered_map<std::type_index, std::unique_ptr<Subscriptions>> SubscriptionsMap;
    static SubscriptionsMap* m_Handlers;

public:
    // subscribe a handler to a templated message type
    template <class T>
    static void const Subscribe(std::function<void (const T&)> handler)
    {
        auto& subscriptions = (*m_Handlers)[typeid(T)];
        if (subscriptions == nullptr)
        {
            // add a new subscriptions list to the type handlers list
            subscriptions = make_unique<Subscriptions>();
            (*m_Handlers)[typeid(T)] = std::move(subscriptions);
        }

        // add the handler to the subscriptions list for the type
        auto subscription = make_unique<Subscription<T>>(handler);
        subscriptions->push_back(std::move(subscription));
    }

    // unsubscribe a handler from a templated message type
    template <class T>
    static void Unsubscribe(std::function<void (const T&)> handler)
    {
        std::unique_ptr<Subscriptions>& subscriptions = (*m_Handlers)[typeid(T)];
        if (subscriptions != nullptr)
        {
            const auto& subscription = find(subscriptions->begin(), subscriptions->end(), handler);
            if (subscription != subscriptions->end())
            {
                // remove the subscription of the function handler from the subscriptions list
                subscriptions->erase(subscription);
            }
            if (subscriptions->size() == 0)
            {
                // remove the subscriptions from the handlers list
                m_Handlers->erase(typeid(T));
            }
        }
    }

    // publish a message to all subscribers of the type
    template <class T>
    static void Publish(const T& message)
    {
        const std::unique_ptr<Subscriptions>& subscriptions = (*m_Handlers)[typeid(T)];
        if (subscriptions != nullptr)
        {
            for (const auto& subscription : *subscriptions)
            {
                ((Subscription<T>*)(subscription.get()))->Handler(message);
            }
        }
    }
};
//---------------------------------------------------------------------------
} // namespace Messaging
//---------------------------------------------------------------------------
#endif // defined(_WIN32) || defined(__APPLE__) || defined(__linux__)
#endif
