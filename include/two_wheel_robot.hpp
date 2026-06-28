#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <filesystem>
#include <iostream>

#include "rounded_rectangle.hpp"
#include "differential_drive.hpp"

class TwoWheelRobot : public DifferentialDriveRobot {
public:

    TwoWheelRobot(std::string name, sf::Vector2f positions, 
        sf::Color color, MessageBus& bus);
   
protected:
    // The draw loop automatically processes the composite system
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::unique_ptr<sf::CircleShape>  createCircleComponent(float radius, 
                                sf::Vector2f origin, sf::Color color);
        
        
    std::unique_ptr<RoundedRectangleShape> createRoundedComponent(
        sf::Vector2f size, float radius,
        sf::Vector2f origin, [[maybe_unused]]sf::Color color);

private:
    sf::Vector2f m_positions;
    sf::Color m_color;
    sf::Texture m_texture;
    std::vector<std::unique_ptr<sf::Shape>> myShapes;
    float m_radius{50.0};
};