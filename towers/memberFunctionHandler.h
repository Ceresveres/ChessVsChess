#pragma once
#include "EventBus.h"
#include "Events.h"

class HandlerFunctionBase {
public:
    void exec(Event* evnt) {
        call(evnt);
    }
private:
    virtual void call(Event* evnt) = 0;
};

template<class T, class EventType>
class MemberFunctionHandler : public HandlerFunctionBase
{
public:
    typedef void (T::* MemberFunction)(EventType*);

    MemberFunctionHandler(T* instance, MemberFunction memberFunction) : instance{ instance }, memberFunction{ memberFunction } {};

    void call(Event* evnt) {
        (instance->*memberFunction)(static_cast<EventType*>(evnt));
    }
private:
    T* instance;
    MemberFunction memberFunction;
};