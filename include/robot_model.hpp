#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "message_bus.hpp"
#include "rounded_rectangle.hpp"


class RobotModel : public sf::Drawable, public sf::Transformable {
public:
    virtual ~RobotModel() = default;
    virtual std::unique_ptr<RoundedRectangleShape> createRoundedComponent(
                    sf::Vector2f size, float radius,
                    sf::Vector2f origin, sf::Color color) = 0;
    
    virtual std::unique_ptr<sf::CircleShape>  createCircleComponent(float radius, 
                                sf::Vector2f origin, sf::Color color) = 0;

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

};
