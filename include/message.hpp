/**
 * @file message.hpp
 * @brief Declaration of differents message types 
 * use for subscription and publishment.
 *
 * Description: Declares the differents message Types.
 * -------
 * @author EnguessT
 * @date June 29, 2026
 */
#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>

namespace messages {
    /**
     * @brief header class: use by almost all other messages types
     */
    struct Header {
        double stamp_sim{};
        std::uint64_t seq{};
    };

    struct SimulationStarted {};
    struct SimulationStopped {};

    /**
     * @brief  initialize the header and time for simulation
     * @param header: header object
     * @param time: simulation time
     */
        struct SimulationTick {
        Header header;
        double time;
    };

    /**
     * @brief message to pause the simulation
     */
    struct Pause  {};

    /**
     * @brief message to reset the simulation
     */
    struct Reset  {};

    /**
     * @brief message to resume the simulation
     */
    struct Resume {};

     /**
     * @brief message to step the simulation
     * aparam dt: steptime
     */
    struct Step {double dt;};

    /**
     * @brief  message to spawn a robot
     * @param type: type of robot(two wheel, four wheel)
     * @param id: id of robot
     * @param name: name of robot
     * @param position: initial posiotion of the robot
     * @param color: color of the robot
     */
    struct SpawnRobot {
        std::string type;
        std::size_t id;
        std::string name;
        sf::Vector2f position;
        sf::Color color;
    };

    /**
     * @brief  message for velocity command of a robot
     * @param header: header type
     * @param target: ID of robot
     * @param left: left wheel velocity
     * @param right: right wheel velocity
     */
    struct VelocityCommand {
        Header header;
        std::size_t target;
        double left;
        double right;

        VelocityCommand()= default;
        
        VelocityCommand(std::size_t t, double l, double r) 
        : header{},target(t), left(l), right(r) 
        {}
    };


    /**
     * @brief  message for perform odometry command of a robot
     * @param header: header type
     * @param id: id of robot
     * @param x: x position of the robot
     * @param y: y position of the robot
     * @param theta: orientation of the robot
     */
    struct Odometry {
        Header header;
        std::size_t id;
        double x{};
        double y{};
        double theta{};

        Odometry()= default;
        Odometry(std::size_t t, double x_t, double y_t, double th_t) 
        : header{}, id(t), x(x_t), y(y_t), theta(th_t) 
        {}
    };

    /**
     * @brief  message for perform laser ray casting
     * @param ranges: vector of dooubles
     */
    struct LaserScan {
        std::vector<double> ranges;
    };

    /**
     * @brief  print Odometry message
     */
    inline std::ostream& operator<<(std::ostream& os, const messages::Odometry& o) {
        return os << o.id 
                << " x = " << o.x
                << " y = " << o.y 
                << " theta = " << o.theta;
    } 

    /**
     * @brief  print VelocityCommand message
     */
    inline std::ostream& operator<<(std::ostream& os, const messages::VelocityCommand& v) {
        return os << v.target 
                << " left=" << v.left 
                << " right=" << v.right;
    }

    /**
     * @brief  print SimulationTick message
     */
    inline std::ostream& operator<<(std::ostream& os, const messages::SimulationTick& t) {
        return os << "time=" << t.time;
    }

    /**
     * @brief  print Header message message
     */
    inline std::ostream& operator<<(std::ostream& os, const messages::Header& h) {
        return os << "stamp=" << h.stamp_sim << " seq=" << h.seq;
    }

    /**
     * @brief  print LaserScan message
     */
    inline std::ostream& operator<<(std::ostream& os, const messages::LaserScan& scan) {
        os << "ranges=[";
        for (auto r : scan.ranges) os << r << ",";
        return os << "]";
    }

}