#pragma once

#include <events/Subscriber.h>

#include <unordered_map>
#include <vector>

namespace events {

class Publisher {
public:
    template <typename Topic>
    Subscriber<Topic> subscribe() {
        return Subscriber<Topic>{};
    }

    template <typename Topic, typename... Args>
    void publish(Args&&... args) {}

private:
    struct TopicHasher {
        template <typename Topic>
        size_t operator()(Topic&&) const {
            return typeid(Topic).hash_code();
        }
    };

    // I think I'm going to end up using some type erasure to normalize the
    // callbacks. The important thing here is that we know, on subscribe, that
    // the arguments for the function are correct. We do some evil casting on
    // publish, but we're still ok (I think).
    std::unordered_map<size_t, std::vector<SubscriberBase>, TopicHasher>
            _subscribers;
};

}  // namespace events
