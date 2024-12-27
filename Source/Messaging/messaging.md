# Simple Messaging system for Rad Studio C++ Builder
**A lightweight synchronous messaging/event system for Rad Studio C++ Builder using C++11**

## Overview
This is a simple messaging system designed for use with MVVM, MVC, MVP applications.
The goal was to make it easy to define new messages/events and to deliver them to
multiple subscribers.

Messages/events are subscribed/published by templated types. This allows for subscribing to
only the messages you are interested in handling. It also means that there is no way to
peek on all of the messages sent. A feature I had no use for.

Note: This implementation is not thread safe

## Usage

### How to use
Simply copy the ``Messaging`` folder into your project folder and add ``#include "Event.h"`` and ``#include "Messaging.h"`` in class header file you want to access the messaging system.
Define a private ``::Messaging::Registrar m_Registrar;`` in your class.

**Note:** Do not add the header to your pre-compiled header as it contains code and is not compatible with the PCH system.

### Using the default Events
The default event class allows for a single event by id only and contains no data.
There is a templated ``OnChange`` event class, that takes a single value of any type.
You then subscribe event handlers based on the event class and supplied type.

#### Subscribing to an ``Event`` event
```c++
void Init()
{
        m_Registrar.Subscribe<Event>(OnEvent);
}

void OnEvent(const OnEvent& message)
{
	// TODO: process the message
        if (event.id == "save") {
                ...save object...
        } else if (event.id == "refresh") {
                ...refresh object...
        }
        ...
}
```

#### Subscribing to an ``OnChange`` event
```c++
void Init()
{
        m_Registrar.Subscribe<OnChange<int>>(OnChangeInt);
}

void OnChangeInt(const OnChange<int>& event)
{
	// TODO: process the message
        if (event.id == "event.1") {
                m_Int_1 = event.Value;
        } else if (event.id == "event.2") {
                m_Int_2 = event.Value;
        }
        ...
}
```

### Create a Custom message class
Simply define a new ``class`` with the data you would like to capture.
```c++
class MyMessage : public Event
{
private:
    int m_Value;
	bool m_Flag;
public:
    __fastcall MyMessage(const String& id, int value, bool flag)
    : Event(id)
    , m_Value(value)
    , m_Flag(flag)
    {
    }

    __property  int 	Value = { read = m_Value };
    __property  bool 	Flag  = { read = m_Flag  };
};
```

### Publish a message
Simply call ``Publish<T>()`` with an instantiation of your message type and data items set.
```c++
void Button1::OnClick()
{
        // using the default event type
        ::Messaging::Bus::Publish<Event>(Event("project.onloaded"));
        // using the custom event type
        ::Messaging::Bus::Publish<MyMessage>(MyMessage("NumberBox1.Value.Changed", NumberBox1->Value, NumberBox1->Value > 10));
}

```
### Subscribe to handling a custom message
Simply call ``m_Registrar.Subscribe<T>()`` with your custom message class and the function used to handle the message.
```c++
void Init()
{
        m_Registrar.Subscribe<MyMessage>(HandleMyMessage);
}

void HandleMyMessage(const TMyMessage& message)
{
	// TODO: process the message
}
```

