#pragma once

#include <events/Subscriber.h>
#include <events/constexpr.h>

#include <memory>
#include <unordered_map>

namespace events {

class Publisher {
public:
    template <typename Topic>
    std::unique_ptr<Subscriber<Topic>> subscribe() {
        auto ret = std::make_unique<Subscriber<Topic>>();
        _subscribers.emplace(hashTopic<Topic>(), ret.get());
        return ret;
    }

    template <typename Topic, typename... Args>
    void publish(const Args&... args) {
        auto itp = _subscribers.equal_range(hashTopic<Topic>());
        if (itp.first == _subscribers.end()) {
            return;
        }
        for (auto it = itp.first; it != itp.second; ++it) {
            static_cast<Subscriber<Topic>*>(it->second)->invoke(args...);
        }
    }

private:
    template <typename Topic>
    constexpr size_t hashTopic() const {
        return cx::type_id<Topic>();
    }

    // I think I'm going to end up using some type erasure to normalize the
    // callbacks. The important thing here is that we know, on subscribe, that
    // the arguments for the function are correct. We do some evil casting on
    // publish, but we're still ok (I think).
    //
    // Hash collisions here would be detrimental but also pretty obvious (I
    // think).
    std::unordered_multimap<size_t, void*> _subscribers;
};

}  // namespace events
