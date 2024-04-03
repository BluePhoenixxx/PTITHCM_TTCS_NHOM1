#ifndef ADATAHOOKER_HPP_
#define ADATAHOOKER_HPP_

#include <memory>
#include <queue>
#include <mutex>
#include <Windows.h>
#include "ControlData.hpp"
#define MAXLENGTH 156
// Forward declaration of WindowsInput
class WindowsInput;

// Forward declaration of ControlData

extern ControlData *gControlData;
extern std::mutex gMutex;
class ADataHooker
{
public:
    // // Constructor
    // ADataHooker(ControlData *controlData) : gControlData(controlData) {}
    ADataHooker(ControlData *gControlData);
    // Destructor
    ~ADataHooker() {}

    // Get current timestamp
    static int getCurrTimestamp();

    // Check if activated
    static bool checkIsActivated(bool inputType);

    // Push data
    static void pushMyData(std::shared_ptr<WindowsInput> newInput);

protected:
    // Pointer to ControlData instance

    HHOOK _hooker;
    // Mutex for thread safety
};

#endif // ADATAHOOKER_HPP_
