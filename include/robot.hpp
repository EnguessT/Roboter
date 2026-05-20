#pragma once

#include <string>
#include "message_bus.hpp"

class Robot {
public:
    Robot() = default;

    explicit Robot(std::string name, MessageBus& bus)
    : m_name(std::move(name)) 
    , m_bus(bus)
    {}

    virtual ~Robot() = default;

    // Update the robot position
    virtual void update(double dt, double simTime) = 0;   // Template Method : design pattern

    // print robot infos
    virtual void printStatus() const = 0;

    virtual void reset() {}

    const std::string name() const {return m_name;}

protected:
    std::string m_name{};
    MessageBus& m_bus;
};