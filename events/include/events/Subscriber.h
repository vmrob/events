#pragma once

#include <vector>

namespace events {

template <typename Topic>
class Subscriber {
public:
    void registerCallback(typename Topic::Callback* f) {
        _callbacks.push_back(std::move(f));
    }

    template <typename... Args>
    void invoke(const Args&... args) {
        for (auto& f : _callbacks) {
            f(args...);
        }
    }

private:
    std::vector<typename Topic::Callback*> _callbacks;
};

}  // namespace events
