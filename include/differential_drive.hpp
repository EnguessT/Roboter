#pragma once

#include <SFML/Graphics.hpp>
#include "robot.hpp"
#include "message.hpp"

class DifferentialDriveRobot: public Robot {
public:
    DifferentialDriveRobot(std::string name, sf::Vector2f initPos, MessageBus& bus);
    void update(double dt, double simTime) override;
    void printStatus() const override;
    void reset() override;
    messages::Header makeHeader(double simTime);


protected:
    sf::Vector2f m_initPosition;
    double m_wheelBase{};
    double m_x{};
    double m_y{};
    double m_theta{};
    double m_leftVel{0.5};
    double m_rightVel{0.5};
    std::uint64_t m_odomSeq {0};
};