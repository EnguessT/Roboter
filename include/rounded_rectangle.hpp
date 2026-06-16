#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class RoundedRectangleShape : public sf::Shape {
public:
    RoundedRectangleShape(const sf::Vector2f& size, 
        float radius, unsigned int cornerPointCount = 8);
    void setSize(const sf::Vector2f& size);
    void setCornersRadius(float radius);
    virtual std::size_t getPointCount() const;
    virtual sf::Vector2f getPoint(std::size_t index) const override;

protected:
    sf::Vector2f m_size;
    float m_radius;
    unsigned int m_cornerPointCount;
};

