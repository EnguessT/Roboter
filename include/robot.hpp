#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "message_bus.hpp"
#include "rounded_rectangle.hpp"
#include "message_bus.hpp"

class Robot : public sf::Drawable, public sf::Transformable {
public:
    Robot() = default;

    explicit Robot(std::string name, MessageBus& bus)
    : m_name(std::move(name)) 
    , m_bus(bus)
    {}

    virtual ~Robot() = default;

    virtual std::unique_ptr<RoundedRectangleShape> createRoundedComponent(
                    sf::Vector2f size, float radius,
                    sf::Vector2f origin, sf::Color color) = 0;
    
    virtual std::unique_ptr<sf::CircleShape>  createCircleComponent(float radius, 
                                sf::Vector2f origin, sf::Color color) = 0;

    // Update the robot position
    virtual void update(double dt, double simTime) = 0;   // Template Method : design pattern

    // print robot infos
    virtual void printStatus() const = 0;

    virtual void reset() {}

    const std::string name() const {return m_name;};
    
protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

protected:
    std::string m_name{};
    MessageBus& m_bus;
};