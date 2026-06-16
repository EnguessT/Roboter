#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <filesystem>
#include <iostream>

#include "rounded_rectangle.hpp"
#include "robot_model.hpp"

class FourWheelRobot : public RobotModel {
public:
    FourWheelRobot(sf::Vector2f positions, sf::Color color)
    : m_positions(positions)
    , m_color(color) {

        // Place the entire combined object in the world
        setPosition(m_positions);

        // ---  Main body  ---
        auto body = createRoundedComponent({m_length, m_width}, 15.f, {m_length, m_width},m_color);
        body->setFillColor(sf::Color(128, 128, 128));
        myShapes.push_back(std::move(body));
      

        // ---  Colored part ---
        auto coloredPart = createRoundedComponent({m_length -12.f, m_width - 12.f}, 
                            15.f, {m_length -6.f, m_width - 6.f},m_color);
        coloredPart->setFillColor(m_color);
        myShapes.push_back(std::move(coloredPart));
       
        // ---  Sensor Circle 1 (Offset / Orbiting Hole Part 1) ---
            // ---  Colored Circle ---
        auto sensorCircle1 = createCircleComponent(20.f, 
                                {m_length - 15.f, m_width - 20.f}, sf::Color(128, 128, 128));
        myShapes.push_back(std::move(sensorCircle1));

        // ---  Sensor Circle 2 (Offset / Orbiting Hole Part 2) ---
        auto sensorCircle2 = createCircleComponent(15.f, 
                                {m_length - 20.f, m_width - 25.f}, sf::Color(0, 0, 0));
        myShapes.push_back(std::move(sensorCircle2));

        // Rotate the body by 180 degree
        this->rotate(sf::degrees(180));


        // ---  Wheels ---
        std::filesystem::path dir_path = std::filesystem::current_path();
        std::filesystem::path imagePath {dir_path/"Assets/images/wheel1.png"};
        if (!m_texture.loadFromFile(imagePath)) {
            std::cerr << "Error: Could not load image from " << imagePath << std::endl;
        } else {
            m_texture.setSmooth(true); 
        }

        // --- Front Left Wheel ---
        auto frontLeftWheel = createRoundedComponent({25.f, 10.f}, 
                            5.f, {m_length - 2.f, m_width + 10.f},m_color);
        frontLeftWheel->setTexture(&m_texture);
        myShapes.push_back(std::move(frontLeftWheel));

        // --- Rear Left Wheel ---
        auto rearLeftWheel = createRoundedComponent({25.f, 10.f}, 
                            5.f, {27.f, m_width + 10.f},m_color);
        rearLeftWheel->setTexture(&m_texture);
        myShapes.push_back(std::move(rearLeftWheel));

        // --- Front Right Wheel ---
        auto frontRightWheel = createRoundedComponent({25.f, 10.f}, 
                            5.f, {m_length -  2.f,  0.f},m_color);
        frontRightWheel->setTexture(&m_texture);
        myShapes.push_back(std::move(frontRightWheel));

        // --- Rear Right Wheel ---
         auto rearRightWheel = createRoundedComponent({25.f, 10.f}, 
                            5.f, {27.f,  0.f},m_color);
        rearRightWheel->setTexture(&m_texture);
        myShapes.push_back(std::move(rearRightWheel));
    }

protected:
     // The draw loop automatically processes the composite system
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        // Inherit global transformations (Position, Rotation, Scale)
        states.transform *= getTransform();
       
        // Render components sequentially
        for (const auto&  shape : myShapes)
        {
            target.draw(*shape, states);
        }
    }

    std::unique_ptr<sf::CircleShape>  createCircleComponent(float radius, 
                                sf::Vector2f origin, sf::Color color)  {
        
        std::unique_ptr<sf::CircleShape> circle = std::make_unique<sf::CircleShape>(radius);
        circle->setOrigin(origin);
        circle->setPosition({0.f, 0.f});
        circle->setFillColor(color);

        return circle;
    }

    std::unique_ptr<RoundedRectangleShape> createRoundedComponent(
                    sf::Vector2f size, float radius,
                    sf::Vector2f origin, [[maybe_unused]]sf::Color color) {
        std::unique_ptr<RoundedRectangleShape> rounded = 
                        std::make_unique<RoundedRectangleShape>(size, radius, 8);
        rounded->setOrigin(origin);
        rounded->setPosition({0.f, 0.f});
        return rounded;
    }

private:
    sf::Vector2f m_positions;
    sf::Color m_color;
    sf::Texture m_texture;
    std::vector<std::unique_ptr<sf::Shape>> myShapes;
    float m_length{100.0};
    float m_width{80.0};
};