#pragma once

#include <unordered_map>
#include <typeindex>
#include <mutex>
#include <iostream>
#include "subscriber.hpp"

class MessageBus {
public:
    MessageBus();
    ~MessageBus();  

    void flush();

    /*template<typename T>
    void subscribe(std::function<void(const T&)> callback){
        std::lock_guard<std::mutex> lock(m_mtx);

        auto& vec = m_subscribers[std::type_index(typeid(T))];

        vec.push_back([callback](const void* msg) {
            callback(*static_cast<const T*> (msg)); 
        });
    }*/

    template<typename T>
    void subscribe(std::function<void(const T&)> cb) {

        auto sub = std::make_shared<Subscriber>();
        sub->callback = [cb](const void* msg) {
            cb(*static_cast<const T*>(msg));
        };

        sub->worker = std::thread([sub]() {
            while (true) {
                std::unique_lock<std::mutex> lk(sub->mtx);
                sub->cv.wait(lk, [&]{ return !sub->queue.empty() || !sub->running; });
                if (sub->queue.empty() || !sub->running) break;

                auto anyMsg = std::move(sub->queue.front());
                sub->queue.pop();
                lk.unlock();

                const T& msg = std::any_cast<const T&>(anyMsg);
                sub->callback(&msg);
            }
        });

        std::lock_guard<std::mutex> lock(m_mtx);
        m_subscribers[std::type_index(typeid(T))].push_back(sub);
    }

    template<typename T>
    void publish(const T& message) {
        std::lock_guard<std::mutex> lock(m_mtx);

        m_history[std::type_index(typeid(T))].push_back(message);

        auto it = m_subscribers.find(std::type_index(typeid(T)));
        if (it == m_subscribers.end()) return;

        for (auto& sub : it->second) {
            {
                std::lock_guard<std::mutex> lk(sub->mtx);
                sub->queue.push(message);
            }
            sub->cv.notify_one();
        }
    }

    /*template<typename T>
    void publish(const T& message){
        std::lock_guard<std::mutex> lock(m_mtx);

        //store message in history
        m_history[std::type_index(typeid(T))].push_back(std::any(message));

        //delivers message to subscribers
        auto it = m_subscribers.find(std::type_index(typeid(T)));
        if(it == m_subscribers.end()) return;

        for(auto& callback: it->second) {
            callback(&message);
        }

    } */

    template<typename T>
    const std::vector<std::any>& getHistory() const {
        static const std::vector<std::any> empty;

        auto it = m_history.find(std::type_index(typeid(T)));
        if (it == m_history.end()) return empty;
        return it->second;
        
        //return m_history.at(std::type_index(typeid(T)));
    }

    template<typename T>
    void printHistory(const std::vector<std::any>& hist) {
        std::cout << ">>> PRINTING HISTORY NOW\n";
        for (auto& h : hist) {
            const auto& msg = std::any_cast<const T&>(h);
            std::cout << msg << '\n'; 
        }
    }

private:
    std::unordered_map<std::type_index, std::vector<std::shared_ptr<Subscriber>>> m_subscribers;
    std::unordered_map<std::type_index, std::vector<std::any>> m_history;
    std::mutex m_mtx;
    void stopAllSubscribers();
};