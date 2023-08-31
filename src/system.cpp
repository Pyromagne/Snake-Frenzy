#include "../inc/system.hpp"

void log(std::string log, bool debugMode = false)
{
    if(debugMode)
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
}

void err(std::string err, bool debugMode = false)
{
    if(debugMode)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&t);
        ce::setForegroundColor(50);
        std::cerr << std::put_time(&tm, "[%y:%m:%d]%H:%M:%S");
        ce::setForegroundColor(160);
        std::cerr << " : " << err << std::endl;
        ce::reset();
    }
}

unsigned short genRandom(unsigned short min, unsigned short max)
{
    unsigned short randNum = (rand() % (max - min + 1)) + min;

    return randNum;
}
