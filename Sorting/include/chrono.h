#pragma once

#include <chrono>

class Chrono
{
public:
    Chrono() = default;

    void start();
    void stop();
    double time() const;

private:
    std::chrono::time_point<std::chrono::steady_clock> begin;
    std::chrono::time_point<std::chrono::steady_clock> einde;
};

