#include "../inc/system.hpp"

void log(std::string log)
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);
    ce::setForegroundColor(50);
    std::clog << std::put_time(&tm, "[%y:%m:%d]%H:%M:%S");
    ce::setForegroundColor(190);
    std::clog << " : " << log << std::endl;
    ce::reset();
}

void err(void)
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);
    ce::setForegroundColor(50);
    std::clog << std::put_time(&tm, "[%y:%m:%d]%H:%M:%S");
    ce::setForegroundColor(160);
    std::clog << ": " << std::endl;
}
