/**
 * @file robot_factory.hpp
 * @brief a Factory design pattern class to
 * automatically create robot models
 * ---
 * @author EnguessT
 * @date June 30, 2026
 */

#pragma once
#include "two_wheel_robot.hpp"
#include "four_wheel_robot.hpp"
#include "id_generator.hpp"

class RobotFactory {
public:
    static std::unique_ptr<Robot> create(const messages::SpawnRobot& msg,
                                         MessageBus& bus)
    {
        std::size_t id = IDGenerator::next();

       if (msg.type == "Two wheel") {
            return std::make_unique<TwoWheelRobot>(
                id, msg.name, msg.position, msg.color, bus
            );
        }
        else if (msg.type == "Four wheel") {
            return std::make_unique<FourWheelRobot>(
                id, msg.name, msg.position, msg.color, bus
            );
        }

        throw std::runtime_error("Unknown robot type: " + msg.type);
    }

};
