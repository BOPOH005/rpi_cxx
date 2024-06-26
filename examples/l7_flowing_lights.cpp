#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <vector>
#include <algorithm>
#include "../rpi_cxx.h"

using namespace rpi_cxx;
using namespace std::this_thread;
using namespace std::chrono;

std::atomic<bool> quit;

template <typename T>
void fl_lights(T &pins)
{
    std::for_each(pins.begin(), pins.end(), [](gpio_pin &p) {p.setmode(mode::out);p=level::hight; });
    auto i_pin = pins.begin();
    for (unsigned i = 0; !quit; ++i)
    {
        *i_pin = level::low;
        sleep_for(milliseconds(100));
        *(i_pin++) = level::hight;
        if (i_pin == pins.end())
            i_pin = pins.begin();
    }
}

int main(void)
{
    std::cout << std::unitbuf;
    std::cout << "Урок №7 Световая дорожка" << std::endl
              << "GPIO 2 -Out->  Диод" << std::endl
              << "GPIO 3 -Out->  Диод" << std::endl
              << "GPIO 4 -Out->  Диод" << std::endl
              << "GPIO 14 -Out->  Диод" << std::endl
              << "GPIO 15 -Out->  Диод" << std::endl
              << "GPIO 17 -Out->  Диод" << std::endl
              << "GPIO 18 -Out->  Диод" << std::endl
              << "GPIO 27 -Out->  Диод" << std::endl
              << "quit - для завершения" << std::endl;
    try
    {
        std::thread th([]() {
            std::string cmd;
            while (cmd != "quit")
                std::cin >> cmd;
            quit = true;
        });
        th.detach();

        std::cout << "Управление на основе индексов" << std::endl;
        std::vector<gpio_pin> pins{2, 3, 4, 14, 15, 17, 18, 27};
        fl_lights(pins);
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << "Ошибка! Проверте запуск с sudo";
    }
    catch (...)
    {
        std::cerr << "Нeизвестное исключение";
    }
}