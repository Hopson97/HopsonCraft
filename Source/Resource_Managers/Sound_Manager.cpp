#include "Sound_Manager.h"

#include <thread>

Sound_Manager::Sound_Manager()
{
    std::string path ("Data/Sounds/");
}

Sound_Manager::~Sound_Manager()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
