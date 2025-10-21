// Simple thread-safe logger
#pragma once
#include <mutex>
#include <iostream>
#include <string>

class Logger {
public:
    enum Level { INFO, WARN, ERROR };
    static void log(Level lvl, const std::string& msg) {
        static std::mutex m;
        std::lock_guard<std::mutex> lk(m);
        std::string prefix = (lvl==INFO?"[I] ": (lvl==WARN?"[W] ":"[E] "));
        std::cout << prefix << msg << std::endl;
    }
};
