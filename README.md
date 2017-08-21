# Event bus

A templated event bus. Experimental.

# Requirements

1. can be subclassed and handled with virtual functions
2. can be registered with C++ std::functions<> for generic callbacks
3. can be registered with Lua functions for generic Lua callbacks
4. can support user-added events which are no longer in the engine
5. can support extra levels of specificity for supplying extra conditions to be satisfied before firing event
6. can use a single monitor/listener for multiplexing multiple events into one monitor
