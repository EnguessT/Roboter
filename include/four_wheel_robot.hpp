/**
 * @file four_wheel_robot.hpp
 * @brief Declaration of class FourWheelRobot.
 *
 * Description: Declares the variables and methods of class FourWheelRobot.
 * 
 * Inheritance:
 * DifferentialDriveRobot class in order to create four wheel robot object
 * displayable on a SFML canvas.
 * -------
 * @author EnguessT
 * @date June 29, 2026
 */
#pragma once

#include <vector>
#include <filesystem>
#include <iostream>

#include "differential_drive.hpp"

class FourWheelRobot : public DifferentialDriveRobot {
public:
     /**
     * @brief Constructs a TwoWheelRobot object
     * @param[in] id the id of the robot
     * @param[in] name the name of the robot
     * @param[in] initPos: the initial position of the robot
     * @param[in] color: the color of the robot
     * @param[in] bus a reference to a message_bus object
     */
    FourWheelRobot(std::size_t id,std::string name, sf::Vector2f positions, 
        sf::Color color, MessageBus& bus);
    
protected:
     // The draw loop automatically processes the composite system
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * @brief create a Circle graphic component
     */
    std::unique_ptr<sf::CircleShape>  createCircleComponent(float radius, 
                                sf::Vector2f origin, sf::Color color) override;
    
    /**
     * @brief create a RoundedRectangle graphic component
     */ 
    std::unique_ptr<RoundedRectangleShape> createRoundedComponent(
                    sf::Vector2f size, float radius,
                    sf::Vector2f origin, [[maybe_unused]]sf::Color color) override;
       

private:
    sf::Color m_color;
    sf::Texture m_texture;
    std::vector<std::unique_ptr<sf::Shape>> myShapes;
    float m_length{100.0};
    float m_width{80.0};
};