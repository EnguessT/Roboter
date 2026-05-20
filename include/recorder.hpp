#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include "message.hpp"
#include "message_bus.hpp"

class Recorder {
public:
    explicit Recorder(MessageBus& bus, const std::string& path)
        : m_out(path), m_running(true), m_worker(&Recorder::run, this)
    {
        if (!m_out.is_open()) {
            std::cerr << "Recorder: failed to open " << path << "\n";
        }

        bus.subscribe<messages::Odometry>(
            [this](const messages::Odometry& o){
                enqueue("Odometry", o);
            });

        bus.subscribe<messages::VelocityCommand>(
            [this](const messages::VelocityCommand& v){
                enqueue("VelocityCommand", v);
            });

        bus.subscribe<messages::SimulationTick>(
            [this](const messages::SimulationTick& t){
                enqueue("SimulationTick", t);
            });
    }

    ~Recorder() {
        {
            std::lock_guard<std::mutex> lock(m_mtx);
            m_running = false;
        }
        m_cv.notify_one();
        if (m_worker.joinable())
            m_worker.join();
        if (m_out.is_open())
            m_out.close();
    }

private:
    struct Item {
        std::string type;
        std::string text;
    };

    std::ofstream m_out;
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::queue<Item> m_queue;
    bool m_running = false;
    std::thread m_worker;

    template<typename T>
    void enqueue(const std::string& type, const T& msg) {
        std::ostringstream oss;
        oss << type << " " << msg;

        {
            std::lock_guard<std::mutex> lock(m_mtx);
            m_queue.push({type, oss.str()});
        }
        m_cv.notify_one();
    }

    void run() {
        while (true) {
            Item item;
            {
                std::unique_lock<std::mutex> lock(m_mtx);
                m_cv.wait(lock, [&]{
                    return !m_queue.empty() || !m_running;
                });

                if (!m_running && m_queue.empty())
                    break;

                item = std::move(m_queue.front());
                m_queue.pop();
            }

            if (m_out.is_open()) {
                m_out << item.text << '\n';
            }
        }
    }
};
