#pragma once
#include <iostream>

#include "message.hpp"
#include "message_bus.hpp"

class Logger {
public:
    Logger(MessageBus& bus) {
        // Sunscribe to the velocity
        bus.subscribe<messages::VelocityCommand>(
            [this](const messages::VelocityCommand& msg) {
                logVelocity(msg);
            }
        );

        //Subscribe to odometry
        bus.subscribe<messages::Odometry>(
            [this](const messages::Odometry& msg) {
                logOdometry(msg);
            }
        );

        //subscribe to simulation ticks
        bus.subscribe<messages::SimulationTick>(
            [this](const messages::SimulationTick& msg) {
                logTick(msg);
            }
        );
    }

private:
    void logVelocity(const messages::VelocityCommand& v) {
        std::cout << "[LOG] VelocityCommand from " << v.target 
                  << " left = " << v.left
                  << " right = " << v.right << '\n';
        }

    void logOdometry(const messages::Odometry& o) {
        std::cout << "[LOG] Odometry " << o.name
                  << " x = " << o.x
                  << " y = " << o.y
                  << " theta = " << o.theta << '\n';
    }

    void logTick(const messages::SimulationTick& t) {
        std::cout << "[LOG] Tick time = " << t.time << '\n';
    }
};
