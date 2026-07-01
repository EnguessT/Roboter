/**
 * @file robot.hpp
 * @brief Declaration of abstract class Robot.
 *
 * Description: Declares the variables and methods of class Robot.
 * 
 * Inheritance:
 * SFML class sf::Drawable and sf::Transformable to perform 
 * graphic display on a SFML canvas.
 * -------
 * @author EnguessT
 * @date June 29, 2026
 */
#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "message_bus.hpp"
#include "rounded_rectangle.hpp"

class Robot : public sf::Drawable, public sf::Transformable {
public:
    // default constructor
    Robot() = default;

    /**
     * @brief Constructs a Robot object
     * 
     * @param[in] name the name of the robot
     * @param[in] bus a reference to a message_bus object
     */
    explicit Robot(std::size_t id,std::string name, MessageBus& bus)
    : m_id(id)
    , m_name(std::move(name)) 
    , m_bus(bus)
    {}

    // default desctructor
    virtual ~Robot() = default;

    /**
     * @brief Update the robot position during the simulation
     * 
     * @param[in] dt: the time step
     * @param[in] simTime: the simulation duration time
     */
    virtual void update(double dt, double simTime) = 0;   // Template Method : design pattern

    /**
     * @brief Print robot informations, name, messages
     */
    virtual void printStatus() const = 0;


    /**
     * @brief reset robot's initial information
     */
    virtual void reset() {}

    /**
     * @brief get the name of a robot
     */
    const std::string& name() const {return m_name;};

    /**
     * @brief get the ID of a robot
     */
    std::size_t id() const { return m_id;}

    /**
     * @brief create a RoundedRectangle graphic component
     */
    virtual std::unique_ptr<RoundedRectangleShape> createRoundedComponent(
                    sf::Vector2f size, float radius,
                    sf::Vector2f origin, sf::Color color) = 0;
    
    /**
     * @brief create a Circle graphic component
     */
    virtual std::unique_ptr<sf::CircleShape>  createCircleComponent(float radius, 
                                sf::Vector2f origin, sf::Color color) = 0;

    
protected:
    /**
     * @brief draw graphic components on the sfml canvas
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
    
    std::size_t m_id;
    std::string m_name{};
    MessageBus& m_bus;
};