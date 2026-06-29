/**
 * @file simulator.hpp
 * @brief Declaration of class Simulator.
 *
 * Description: Declares the variables and methods of class Simulator.
 * 
 * proceed with the simulation of all created robots.
 * -------
 * @author EnguessT
 * @date June 29, 2026
 */

#pragma once

#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "robot.hpp"
#include "message.hpp"


class Simulator {
public:
    /**
     * Constructor method
     * @brief create a simulator object 
     *  
    */ 
    Simulator();

    /***
     * Destructor
     * @brief destroy the Simulator object
     */  
    ~Simulator();

    /**
     * @brief add a created Robot object to the vector of Robots
     * displayed on the SFML canvas
     * @param[in] robot: an unique_ptr of Robot object
     * @param[out] void
     */
    void addRobot(std::unique_ptr<Robot> robot);
    //void update(double dt);

    /**
     * @brief print all created Robot objects added to the Canvas
     * @param[in] void
     * @param[out] void
     */
    void printAll() const;

    /**
     * @brief start the simulation's run
     * @param[in] dt: the simulation time
     * @param[out] void
     */
    void start(double dt);

    /**
     * @brief stop the simulation's run
     * @param[in] void
     * @param[out] void
     */
    void stop();

    /**
     * @brief create and return a Header object
     * @param[in] simTime: the simulation time
     * @param[out] messages::Header  Header object
     */
    messages::Header makeHeader(double simTime);

    /**
     * @brief take in a velocity commands for 
     * forward kinematic
     * @param[in] target: name of the robot
     * @param[in] left, right: speed of left and riight wheel
     * @param[in] simTime: the simulation time  
     */
    messages::VelocityCommand makeVelocityCommand(const std::string& target, 
                double left, double right, double simTime);

    /**
     * @brief create a bus object
     * @param[in] void
     * @param[out] MessageBus& MessageBus object reference
     */
    MessageBus& bus();

private:
    std::vector<std::unique_ptr<Robot>> m_robots;  //vector of robots created
    /**
     * @brief proceed the threaded loop of all robot created
     * @param[in] dt: time step
     * @param[out] void
     */
    void loop(double dt);
    
    std::thread m_worker;
    std::atomic<bool> m_running{false};
    mutable std::mutex m_mtx;  // to protect robot updates
    std::mutex m_sleepMutex;  // used for timed waits
    std::condition_variable m_cv;
    MessageBus m_bus;
    double m_lastDt = 0.1;
    std::uint64_t m_tickSeq {0};
    std::uint64_t m_cmdSeq = 0;
    double simTime {};
    
};