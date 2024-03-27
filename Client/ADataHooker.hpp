#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <mutex>
#include <memory>
#include "ControlData.hpp"
#include "WindowsInput.hpp"

extern ControlData *gControlData;
extern std::mutex gMutex;

class ADataHooker {
public:
    int getCurrTimestamp();
    bool checkIsActivated(bool inputType);
    void pushMyData(std::shared_ptr<WindowsInput> newInput);
};