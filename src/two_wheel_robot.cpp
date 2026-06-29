/**
 * @file two_wheel_robot.cpp
 * @brief Definition of class TwoWheelRobot.
 *
 * Description: Defines the methods of class TwoWheelRobot.
 * 
 * -------
 * @author EnguessT
 * @date June 29, 2026
 */

#include "../include/two_wheel_robot.hpp"


TwoWheelRobot::TwoWheelRobot(std::string name, sf::Vector2f positions, 
        sf::Color color, MessageBus& bus)
    : DifferentialDriveRobot(name, positions, bus)
    , m_color(color) {

    // WheeelBase the distance between the left and right wheels
    // wheelbase = mainbody diameter(50.f * 2 = 100) +  half wheels length(10.f/2 = 5.f)
    m_wheelBase = 105.f;

    // Place the entire combined object in the world
    setPosition(m_initPosition);

    // wheels Textures
    std::filesystem::path dir_path = std::filesystem::current_path();
    std::filesystem::path texturePath {dir_path/"Assets/images/wheel1.png"};
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Error: Could not load image from " << texturePath << std::endl;
    } else {
        m_texture.setSmooth(true); 
    }

    // ---  Main Body  ---
    auto  body = createCircleComponent(m_radius, {m_radius, m_radius}, 
                        sf::Color(128, 128, 128));
    myShapes.push_back(std::move(body));

    // ---  Colored Circle ---
    auto coloredCircle = createCircleComponent(40.f, {40.f, 40.f}, m_color);
    myShapes.push_back(std::move(coloredCircle));

    // ---  Inner Circle 1 (Offset / Orbiting Hole Part 1) ---
    auto innerCircle1 = createCircleComponent(20.f, {20.f, 20.f}, sf::Color(128, 128, 128));
    myShapes.push_back(std::move(innerCircle1));

    // ---  Inner Circle 2 (Offset / Orbiting Hole Part 2) ---
    auto innerCircle2 = createCircleComponent(15.f, {15.f, 15.f}, sf::Color(0, 0, 0));
    myShapes.push_back(std::move(innerCircle2));

    // ---  Sensor Circle 1 ---
    auto sensorCircle1 = createCircleComponent(18.f, {m_radius, m_radius}, sf::Color(128, 128, 128));
    myShapes.push_back(std::move(sensorCircle1));

        // ---  Sensor Circle 2 ---
    auto sensorCircle2 = createCircleComponent(12.f, {m_radius -6.f, m_radius - 6.f}, sf::Color(0, 0, 0));
    myShapes.push_back(std::move(sensorCircle2));

    this->rotate(sf::degrees(135));

    // ---  WHEELS  ---
    // ---  Left Wheels ---
    auto leftWheel = createRoundedComponent({30.f, 10.f}, 5.f, {15.f, m_radius + 5.f},m_color);
    leftWheel->rotate(sf::degrees(45));
    leftWheel->setTexture(&m_texture);
    myShapes.push_back(std::move(leftWheel));

    // ---  Right Wheel ---
    auto rightWheel = createRoundedComponent({30.f, 10.f}, 5.f, {15.f, - m_radius + 5.f},m_color);
    rightWheel->rotate(sf::degrees(45));
    rightWheel->setTexture(&m_texture);
    myShapes.push_back(std::move(rightWheel));
}

void TwoWheelRobot::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Inherit global transformations (Position, Rotation, Scale)
    states.transform *= getTransform();
    
    // Render components sequentially
    for (const auto&  shape : myShapes)
    {
        target.draw(*shape, states);
    }
}

std::unique_ptr<sf::CircleShape>  TwoWheelRobot::createCircleComponent(float radius, 
                                sf::Vector2f origin, sf::Color color)  {
        
    std::unique_ptr<sf::CircleShape> circle = std::make_unique<sf::CircleShape>(radius);
    circle->setOrigin(origin);
    circle->setPosition({0.f, 0.f});
    circle->setFillColor(color);

    return circle;
}

std::unique_ptr<RoundedRectangleShape> TwoWheelRobot::createRoundedComponent(
        sf::Vector2f size, float radius,
        sf::Vector2f origin, [[maybe_unused]]sf::Color color) {

    std::unique_ptr<RoundedRectangleShape> rounded = 
                    std::make_unique<RoundedRectangleShape>(size, radius, 8);
    rounded->setOrigin(origin);
    rounded->setPosition({0.f, 0.f});
    return rounded;
}