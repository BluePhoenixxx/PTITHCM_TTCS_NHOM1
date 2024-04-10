#include "stdafx.h"
#include "WindowsInput.hpp"
// khởi tạo WIndowsInput
WindowsInput::WindowsInput(int key, std::pair<int, int> pos, int time, char proc[256]) : _key(key), _pos(pos), _time(time)
{
    memset(_proc, '\0', sizeof(char) * 256);
    // đảm bảo rằng mảng _proc sẽ được khởi tạo với chuỗi rỗng.
    strncpy_s(_proc, proc, 256);
    // được sử dụng để đảm bảo rằng việc sao chép sẽ không gây ra lỗi tràn bộ đệm.
}