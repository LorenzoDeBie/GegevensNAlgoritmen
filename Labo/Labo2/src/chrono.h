#ifndef CHRONO_H
#define CHRONO_H

#include <chrono>

class Chrono
{
public:
    Chrono() = default;

    void start();
    void stop();
    double tijd() const;

private:
    std::chrono::time_point<std::chrono::steady_clock> begin;
    std::chrono::time_point<std::chrono::steady_clock> einde;
};

void Chrono::start()
{
    begin = std::chrono::steady_clock::now();
}

void Chrono::stop()
{
    einde = std::chrono::steady_clock::now();
}

double Chrono::tijd() const
{
    std::chrono::duration<double> diff(einde - begin);

    return diff.count();
}

#endif

