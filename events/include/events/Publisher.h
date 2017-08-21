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
        _subscribers.resize(std::max(Topic::Id + 1, _subscribers.size()));
        auto ret = std::make_unique<Subscriber<Topic>>();
        _subscribers[Topic::Id].push_back(ret.get());
        return ret;
    }

    template <typename Topic, typename... Args>
    void publish(const Args&... args) {
        if (_subscribers.size() < Topic::Id) {
            return;
        }
        for (auto it = _subscribers[Topic::Id].begin();
             it != _subscribers[Topic::Id].end();
             ++it) {
            static_cast<Subscriber<Topic>*>(*it)->invoke(args...);
        }
    }

private:
    std::vector<std::vector<void*>> _subscribers;
};

}  // namespace events
