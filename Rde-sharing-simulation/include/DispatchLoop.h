// DispatchLoop: runs the dispatcher's periodic dispatch_step in a background thread
#pragma once
#include "Dispatcher.h"
#include <thread>
#include <atomic>
#include <chrono>

class DispatchLoop {
public:
    DispatchLoop(Dispatcher& d): disp(d), running(false) {}
    ~DispatchLoop() { stop(); }

    void start(std::chrono::milliseconds interval = std::chrono::milliseconds(100)) {
        if (running.load()) return;
        running = true;
        worker = std::thread([this, interval]() {
            while (running.load()) {
                disp.dispatch_step();
                std::this_thread::sleep_for(interval);
            }
        });
    }

    void stop() {
        if (!running.load()) return;
        running = false;
        if (worker.joinable()) worker.join();
    }

private:
    Dispatcher& disp;
    std::thread worker;
    std::atomic<bool> running;
};
