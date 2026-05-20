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
    Simulator();
    ~Simulator();

    void addRobot(std::unique_ptr<Robot> robot);
    //void update(double dt);
    void printAll() const;

    void start(double dt);
    void stop();

    messages::Header makeHeader(double simTime);
    messages::VelocityCommand makeVelocityCommand(const std::string& target, 
                double left, double right, double simTime);

    MessageBus& bus();

private:
    std::vector<std::unique_ptr<Robot>> m_robots;
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