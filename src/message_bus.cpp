#include "../include/message_bus.hpp"

MessageBus::MessageBus() = default;

MessageBus::~MessageBus() {
    stopAllSubscribers();
}

void MessageBus::flush() {
    std::lock_guard<std::mutex> lock(m_mtx);
    for(auto& [type, vec] : m_subscribers) {
        for(auto& sub : vec) {
            std::unique_lock<std::mutex> lk(sub->mtx);
            sub->cv.wait(lk, [&]{
                return sub->queue.empty();
            });
        }
    }
}

void MessageBus::stopAllSubscribers() {
    std::lock_guard<std::mutex> lock(m_mtx);
     for(auto& [type, vec]: m_subscribers) {
        for(auto& sub : vec) {
            {
                std::lock_guard<std::mutex> lk(sub->mtx);
                sub->running = false;
            }
            sub->cv.notify_one();
        }
    }
    for(auto& [type, vec] : m_subscribers) {
        for(auto& sub : vec) {
            if(sub->worker.joinable()) {
                sub->worker.join();
            }
        }
    }

}