#include <cmath>
#include <iostream>
#include "../include/message.hpp"
#include "../include/differential_drive.hpp"

                        
DifferentialDriveRobot:: DifferentialDriveRobot(std::string name, double wheelBase, 
                MessageBus& bus)
    : Robot(std::move(name), bus)
    , m_wheelBase(wheelBase) {

    m_bus.subscribe<messages::VelocityCommand>(
        [this](const messages::VelocityCommand& cmd) {
            if(cmd.target == m_name) {
                m_leftVel = cmd.left;
                m_rightVel = cmd.right;
            }
        }
    );   
}

void DifferentialDriveRobot::update(double dt, double simTime) {
    double vel = (m_leftVel + m_rightVel) * 0.5;
    double angVel = (m_rightVel - m_leftVel) / m_wheelBase;
    
    m_x     += vel * std::cos(m_theta) * dt;
    m_y     += vel * std::sin(m_theta) * dt; 
    m_theta += angVel * dt;

    //odometry message
    messages::Odometry odom;
    odom.header.stamp_sim = simTime;
    odom.header.seq = m_odomSeq++;
    odom.name = m_name;
    odom.x = m_x;
    odom.y = m_y;
    odom.theta = m_theta;
    m_bus.publish(odom);

    messages::VelocityCommand velocity;
    velocity.header.stamp_sim = simTime;
    velocity.header.seq = m_odomSeq++;
    velocity.left = m_leftVel;
    velocity.right = m_rightVel;
    velocity.target = m_name;
    m_bus.publish(velocity);

}

void DifferentialDriveRobot::printStatus() const
{
    std::cout << m_name << " @ (" << m_x << " , " << m_y << "), θ = " << m_theta << '\n';
}

void DifferentialDriveRobot::reset() {
    m_x = m_y = m_theta = 0.0;
    m_leftVel = m_rightVel = 0.0;
}

messages::Header DifferentialDriveRobot::makeHeader(double simTime){
    messages::Header h;
    h.stamp_sim = simTime;
    h.seq = m_odomSeq++;
    return h;
}
