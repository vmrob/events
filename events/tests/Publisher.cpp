#include <events/Publisher.h>

#include <gtest/gtest.h>

struct Topic1 {
    using Callback = void(bool, double, const char*);
};

TEST(Publisher, basics) {
    events::Publisher p;

    auto subscriber = p.subscribe<Topic1>();
    subscriber.registerCallback([](bool, double, const char*) {
        std::cout << "called" << std::endl;
    });

    p.publish<Topic1>(true, 1.5, "hello world");
}
