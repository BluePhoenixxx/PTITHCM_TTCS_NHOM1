#ifndef ADATAHOOKER_HPP_
#define ADATAHOOKER_HPP_
#include <mutex>
#include <Windows.h>
#include "ControlData.hpp"
#include "WindowsInput.hpp"
#define MAXLENGTH 255

extern ControlData *gControlData;
extern std::mutex gMutex;

class ADataHooker
{
private:
    ControlData *m_controlData; // Member variable to store gControlData
protected:
    HHOOK _hooker; // Protected member variable

public:
    ADataHooker(ControlData *controlData) : m_controlData(controlData) {} // Constructor
    ADataHooker();
    ~ADataHooker() = default; // Destructor

    static ULONG getCurrTimestamp();                                // Get current timestamp
    static bool checkIsActivated(bool inputType);                   // Check if activated
    static void pushMyData(std::shared_ptr<WindowsInput> newInput); // Push data
};

// Definition of member functions outside the class

#endif // ADATAHOOKER_HPP_