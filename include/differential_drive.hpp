#pragma once

#include "robot.hpp"
#include "message.hpp"

class DifferentialDriveRobot: public Robot {
public:
    DifferentialDriveRobot(std::string name, double wheelBase, MessageBus& bus);
    void update(double dt, double simTime) override;
    void printStatus() const override;
    void reset() override;
    messages::Header makeHeader(double simTime);


private:
    double m_wheelBase{};
    double m_x{};
    double m_y{};
    double m_theta{};
    double m_leftVel{0.5};
    double m_rightVel{0.5};
    std::uint64_t m_odomSeq {0};
};