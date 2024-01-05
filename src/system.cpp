#include "../inc/system.hpp"

void log(std::string log, bool debugMode = false)
{
    if(debugMode)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&t);
        ce::setForegroundColor(50);
        std::clog << std::put_time(&tm, "[%y:%m:%d] %H:%M:%S");
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
        std::cerr << std::put_time(&tm, "[%y:%m:%d] %H:%M:%S");
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

sf::Vector2i GetDesktopResolution(void)
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    
    return sf::Vector2i(desktop.right, desktop.bottom);
}

sf::Color hsv(int hue, float sat, float val)
{
  hue %= 360;
  while(hue<0) hue += 360;

  if(sat<0.f) sat = 0.f;
  if(sat>1.f) sat = 1.f;

  if(val<0.f) val = 0.f;
  if(val>1.f) val = 1.f;

  int h = hue/60;
  float f = float(hue)/60-h;
  float p = val*(1.f-sat);
  float q = val*(1.f-sat*f);
  float t = val*(1.f-sat*(1-f));

  switch(h)
  {
    default:
    case 0:
    case 6: return sf::Color(val*255, t*255, p*255);
    case 1: return sf::Color(q*255, val*255, p*255);
    case 2: return sf::Color(p*255, val*255, t*255);
    case 3: return sf::Color(p*255, q*255, val*255);
    case 4: return sf::Color(t*255, p*255, val*255);
    case 5: return sf::Color(val*255, p*255, q*255);
  }
}