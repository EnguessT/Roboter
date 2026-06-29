/**
 * @file differential_drive.hpp
 * @brief Declaration of abstract class DifferentialDriveRobot.
 *
 * Description: Declares the variables and methods of class DifferentialDriveRobot.
 * 
 * Inheritance:
 * Robot class in order to create differenetial robot objects
 * displayable on a SFML canvas.
 * -------
 * @author EnguessT
 * @date June 29, 2026
 */
#pragma once

#include <SFML/Graphics.hpp>
#include "robot.hpp"
#include "message.hpp"

class DifferentialDriveRobot: public Robot {
public:
    /**
     * @brief Constructs a DifferentialDriveRobot object
     * 
     * @param[in] name the name of the robot
     * @param[in] initPos: the initial position of the robot
     * @param[in] bus a reference to a message_bus object
     */
    DifferentialDriveRobot(std::string name, sf::Vector2f initPos, MessageBus& bus);

    /**
     * @brief Update the robot position during the simulation
     * 
     * @param[in] dt: the time step
     * @param[in] simTime: the simulation duration time
     */
    void update(double dt, double simTime) override;

    /**
     * @brief Print robot informations, name, messages
     */
    void printStatus() const override;

    /**
     * @brief reset robot's initial information
     */
    void reset() override;

    /**
     * @brief create a header object 
     * @param[in] simTime : the simulation duration time
     */
    messages::Header makeHeader(double simTime);

protected:
    sf::Vector2f m_initPosition;
    double m_wheelBase{};   // distance between the wheels
    double m_x{};           // x position
    double m_y{};           // y position
    double m_theta{};       // theta angle
    double m_leftVel{0.5};  // left wheel velocity
    double m_rightVel{0.5}; // right wheel velocity
    std::uint64_t m_odomSeq {0};
};