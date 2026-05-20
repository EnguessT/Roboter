#pragma once

#include <vector>
#include <cstdint>
#include <string>

namespace messages {

    struct Header {
        double stamp_sim{};
        std::uint64_t seq{};
    };

    struct SimulationStarted {};
    struct SimulationStopped {};

    struct SimulationTick {
        Header header;
        double time;
    };

    struct Pause  {};
    struct Reset  {};
    struct Resume {};
    struct Step {double dt;};

    struct SpawnRobot {
        std::string name;
        double wheelBase;
    };

    struct VelocityCommand {
        Header header;
        std::string target;
        double left;
        double right;

        VelocityCommand()= default;

        VelocityCommand(std::string t, double l, double r) 
        : header{},target(std::move(t)), left(l), right(r) 
        {}
    };

    struct Odometry {
        Header header;
        std::string name;
        double x{};
        double y{};
        double theta{};

        Odometry()= default;
        
        Odometry(std::string t, double x_t, double y_t, double th_t) 
        : header{}, name(std::move(t)), x(x_t), y(y_t), theta(th_t) 
        {}
    };

    struct LaserScan {
        std::vector<double> ranges;
    };


    inline std::ostream& operator<<(std::ostream& os, const messages::Odometry& o) {
        return os << o.name 
                << " x = " << o.x
                << " y = " << o.y 
                << " theta = " << o.theta;
    } 

    inline std::ostream& operator<<(std::ostream& os, const messages::VelocityCommand& v) {
        return os << v.target 
                << " left=" << v.left 
                << " right=" << v.right;
    }

    inline std::ostream& operator<<(std::ostream& os, const messages::SimulationTick& t) {
        return os << "time=" << t.time;
    }

    inline std::ostream& operator<<(std::ostream& os, const messages::Header& h) {
        return os << "stamp=" << h.stamp_sim << " seq=" << h.seq;
    }

    inline std::ostream& operator<<(std::ostream& os, const messages::LaserScan& scan) {
        os << "ranges=[";
        for (auto r : scan.ranges) os << r << ",";
        return os << "]";
    }

}