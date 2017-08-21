#include <events/Publisher.h>

#include <gtest/gtest.h>

struct Topic1 {
    using Callback = void(bool, double, const char*);
};

size_t gCalled = 0;

TEST(Publisher, basics) {
    events::Publisher p;

    auto subscriber = p.subscribe<Topic1>();

    subscriber->registerCallback([](bool a, double b, const char* c) {
        ++gCalled;
        EXPECT_TRUE(a);
        EXPECT_EQ(b, 1.5);
        EXPECT_EQ(c, "hello world");
    });

    p.publish<Topic1>(true, 1.5, "hello world");

    EXPECT_EQ(gCalled, 1);
}
