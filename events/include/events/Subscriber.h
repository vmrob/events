#pragma once

namespace events {

class SubscriberBase {};

template <typename Topic>
class Subscriber : public SubscriberBase {
public:
    template <typename F>
    void registerCallback(F&& f) {}
};

}  // namespace events
