#include "stdafx.h"
#include "ADataHooker.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <ctime>
std::mutex gMutex;
ControlData *gControlData;

// hàm lấy thời gian hiện tại
ULONG ADataHooker::getCurrTimestamp()
{

    SYSTEMTIME st;
    std::tm tm;

    GetLocalTime(&st);

    tm.tm_sec = st.wSecond;
    tm.tm_min = st.wMinute;
    tm.tm_hour = st.wHour;
    tm.tm_mday = st.wDay;
    tm.tm_mon = st.wMonth - 1;
    tm.tm_year = st.wYear - 1900;
    tm.tm_isdst = -1;
    std::time_t t = std::mktime(&tm);

    return (t);
}
// kiểm tra xem tiến trình có đang chạy hay không

bool ADataHooker::checkIsActivated(bool inputType)
{
    gMutex.lock();
    if (gControlData->_state.isPaused() || !inputType)
    {
        gMutex.unlock();
        return (false);
    }
    gMutex.unlock();
    return (true);
}
// thêm một đối tượng WindowsInput vào một hàng đợi (queue) được bảo vệ bởi mutex.
void ADataHooker::pushMyData(std::shared_ptr<WindowsInput> newInput)
{
    gMutex.lock();
    gControlData->_keys.push(newInput);
    gMutex.unlock();
}