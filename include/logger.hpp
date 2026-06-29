/**
 * @file logger.hpp
 * @brief Declaration of variables and methods of class logger
 *
 * Description: record all information about subscription messages.
 * -------
 * @author EnguessT
 * @date June 29, 2026
 */

#pragma once
#include <iostream>

#include "message.hpp"
#include "message_bus.hpp"

class Logger {
public:

    /**
     * @brief create a Logger object
     * @param[out] bus: a MessageBus object
     */
    Logger(MessageBus& bus) {
        // Subscribe to the velocity
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
    /**
     * @brief print velocityCommand infos
     * @param[out] v: VelocityCommand object reference
     * @return void
     */
    void logVelocity(const messages::VelocityCommand& v) {
        std::cout << "[LOG] VelocityCommand from " << v.target 
                  << " left = " << v.left
                  << " right = " << v.right << '\n';
        }

    /**
     * @brief print Odometry infos
     * @param[out] o: Odometry object reference
     * @return void
     */
    void logOdometry(const messages::Odometry& o) {
        std::cout << "[LOG] Odometry " << o.name
                  << " x = " << o.x
                  << " y = " << o.y
                  << " theta = " << o.theta << '\n';
    }

    /**
     * @brief print SimulationTick infos
     * @param[out] t: SimulationTick object reference
     * @return void
     */
    void logTick(const messages::SimulationTick& t) {
        std::cout << "[LOG] Tick time = " << t.time << '\n';
    }
};
