/**
 * @file recorder.hpp
 * @brief Declaration of variables and methods of class Recorder
 *
 * Description: record all information about subscription messages
 * in a .log file.
 * -------
 * @author EnguessT
 * @date June 29, 2026
 */

#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include "message.hpp"
#include "message_bus.hpp"

class Recorder {
public:

    /**
     * @brief create a Recorder object
     * @param[in] bus: a MessageBus object reference
     * @param[in] path: the path to the record .log file 
     */
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

    /**
     * @brief stop the recording and destroy a Recorder object
     */
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

    /**
     * @brief Object to hold a message type in string form
     * and string form of message to record
     */    
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

    /**
     * @brief place the message object to the recording queue
     * 
     * @tparam T the type of message
     * @param[in] type: string title of the message type
     * @param[in] msg: message object reference
     * @return void
     */
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

    /**
     * @brief start the recording 
     * 
     * @param[in] void
     * @return void
     */
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
