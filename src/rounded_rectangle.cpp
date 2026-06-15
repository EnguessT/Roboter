#include "../include/rounded_rectangle.hpp"


RoundedRectangleShape::RoundedRectangleShape(const sf::Vector2f& size, 
            float radius, unsigned int cornerPointCount)
    : m_size(size), m_radius(radius), m_cornerPointCount(cornerPointCount) {
        
    float maxRadius = std::min(m_size.x, m_size.y) / 2.0f;
    if (m_radius > maxRadius) m_radius = maxRadius;
    update();
}

void RoundedRectangleShape::setSize(const sf::Vector2f& size) {
    m_size = size;
    update();
}

void RoundedRectangleShape::setCornersRadius(float radius) {
    m_radius = radius;
    update();
}

std::size_t RoundedRectangleShape::getPointCount() const {
    return m_cornerPointCount * 4;
}

sf::Vector2f RoundedRectangleShape::getPoint(std::size_t index) const {
    if (m_radius <= 0.0f)
    {
        // Fallback to standard rectangle corners if radius is zero
        if (index == 0) return {0, 0};
        if (index == 1) return {m_size.x, 0};
        if (index == 2) return {m_size.x, m_size.y};
        return {0, m_size.y};
    }

    // Determine which corner quadrant we are in
    size_t quadrant = index / m_cornerPointCount;
    size_t indexInQuadrant = index % m_cornerPointCount;

    // Base angle offsets for Top-Right, Bottom-Right, Bottom-Left, Top-Left
    float centerAngles[] = { 270.0f, 0.0f, 90.0f, 180.0f };
    float centerAngle = centerAngles[quadrant];

    // Linearly interpolate angle inside the specific corner arc
    float deltaAngle = 90.0f / (m_cornerPointCount - 1);
    float angle = (centerAngle + indexInQuadrant * deltaAngle) * 3.14159265f / 180.0f;

    // Locate the origin point of the corner arc center
    sf::Vector2f arcCenter;
    switch (quadrant)
    {
        case 0: arcCenter = { m_size.x - m_radius, m_radius }; break;             // Top-Right
        case 1: arcCenter = { m_size.x - m_radius, m_size.y - m_radius }; break;  // Bottom-Right
        case 2: arcCenter = { m_radius, m_size.y - m_radius }; break;             // Bottom-Left
        case 3: arcCenter = { m_radius, m_radius }; break;                        // Top-Left
    }

    // Calculate final point position on the circle boundary
    return { arcCenter.x + m_radius * std::cos(angle), arcCenter.y + m_radius * std::sin(angle) };
}


