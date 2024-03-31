#ifndef ADATAHOOKER_HPP_
#define ADATAHOOKER_HPP_

#include <memory>
#include <queue>
#include <mutex>
#include <Windows.h>
#define MAXLENGTH 156
// Forward declaration of WindowsInput
class WindowsInput;

// Forward declaration of ControlData
class ControlData;

class ADataHooker
{
public:
    // Constructor
    ADataHooker(ControlData *controlData) : mControlData(controlData) {}

    // Destructor
    ~ADataHooker() {}

    // Get current timestamp
    static int getCurrTimestamp();

    // Check if activated
    bool checkIsActivated(bool inputType);

    // Push data
    void pushMyData(std::shared_ptr<WindowsInput> newInput);

private:
    // Pointer to ControlData instance
    ControlData *mControlData;

    // Mutex for thread safety
    static std::mutex gMutex;
};

#endif // ADATAHOOKER_HPP_
