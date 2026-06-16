#pragma once

#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <any>
#include <condition_variable>


struct Subscriber {
    std::thread worker;
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<std::any> queue;
    bool running = true;
    std::function<void(const void*)> callback;
};
