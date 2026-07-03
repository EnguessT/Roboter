/**
 * @file simulator.cpp
 * @brief Definition of class Simulator.
 *
 * Description: Defines the methods of class Simulator.
 * 
 * proceed with the simulation of all created robots.
 * -------
 * @author EnguessT
 * @date June 29, 2026
 */

#include <iostream>
#include "../include/message.hpp"
#include "../include/robot_factory.hpp"
#include "../include/simulator.hpp"


Simulator::Simulator() {
    /* create and initialize subscription to messages used for 
    simulation and spawn the robots created */

    m_bus.subscribe<messages::Pause>([this](const messages::Pause&) {
        m_running = false;
    });

    m_bus.subscribe<messages::Resume>([this](const messages::Resume&) {
        if(m_running) {
            start(m_lastDt);
        }
    });

    m_bus.subscribe<messages::Reset>([this](const messages::Reset&) {
        std::lock_guard<std::mutex> lock(m_mtx);
        for(auto& robot : m_robots) {
            robot->reset();
        }
    });

    m_bus.subscribe<messages::SpawnRobot>([this](const messages::SpawnRobot& msg) {
        std::lock_guard<std::mutex> lock(m_mtx);
        
        auto robot = RobotFactory::create(msg, m_bus);
        m_robots.push_back(std::move(robot));
    
    });

    m_bus.subscribe<messages::Step>([this](const messages::Step& msg) { 
        std::lock_guard<std::mutex> lock(m_mtx); 
        for (auto& robot : m_robots) { 
            robot->update(msg.dt, simTime); 
        } 
        // Optionally publish a SimulationTick 
    });

}

Simulator::~Simulator() {
    stop();
}

void Simulator::addRobot(std::unique_ptr<Robot> robot) { std::lock_guard<std::mutex> lock(m_mtx);
    m_robots.push_back(std::move(robot));
}


void Simulator::start(double dt) {
    m_lastDt = dt;
    if (m_running) return;
    m_running = true;
    m_bus.publish(messages::SimulationStarted{});
    m_worker = std::thread(&Simulator::loop, this, dt);
}

void Simulator::stop() 
{
    if(!m_running) return;
    m_running = false;
    
    m_cv.notify_all();

    if (m_worker.joinable()) {
        m_worker.join();
    }
    
    m_bus.publish(messages::SimulationStopped{});
}

void Simulator::loop(double dt) {
    using namespace std::chrono;

    auto next = steady_clock::now();
    double sTime {};

    while(true) {
        auto step = duration_cast<steady_clock::duration>(duration<double>(dt));
        next += step;
        {
            std::lock_guard<std::mutex> lock(m_mtx);
            for(auto& robot: m_robots) {
                try {
                    robot->update(dt,sTime);
                } 
                catch (const std::exception& e) {
                    std::cerr << "Robot error: " << e.what() << '\n';
                }
            }

        }
        sTime += dt;
        simTime = sTime;
        messages::SimulationTick tick_time {.header {},.time = sTime};
        m_bus.publish(tick_time);

        messages::SimulationTick tick;
        tick.header.stamp_sim = sTime;
        tick.header.seq = m_tickSeq++;
        tick.time = sTime;
        m_bus.publish(tick);

        std::unique_lock<std::mutex> lk(m_sleepMutex);
        if(m_cv.wait_until(lk, next, [this] {return !m_running;}))
            break;

        //std::this_thread::sleep_until(next);
    }
}

messages::Header Simulator::makeHeader(double simTime) {
    messages::Header h;
    h.stamp_sim = simTime;
    h.seq = m_tickSeq++;
    return h;
}

messages::VelocityCommand Simulator::makeVelocityCommand( std::size_t id,
    const std::string& name, double left, double right, double simTime) {
    messages::VelocityCommand v;
    v.header.stamp_sim = simTime;
    v.header.seq = m_cmdSeq++;
    v.target = id;
    v.name = name;
    v.left = left;
    v.right = right;
    return v;
}


void Simulator::printAll() const {
    std::lock_guard<std::mutex> lock(m_mtx);
    for (const auto& robot : m_robots) {
        robot->printStatus();
    }
}

MessageBus& Simulator::bus() { 
    return m_bus;
}

const std::vector<std::unique_ptr<Robot>>& Simulator::robots() const {
    return m_robots;
 }
