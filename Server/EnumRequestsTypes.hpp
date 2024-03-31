#ifndef ENUMREQUESTSTYPES_HPP_
#define ENUMREQUESTSTYPES_HPP_

/*
+ RequestCode đc sử dụng để gửi lệnh yêu cầu ở phía server
+ Client sẽ trả lời với mã code phù hợp
*/
enum RequestCode{
    //Các lệnh yêu cầu
    PING = 0,
    USER,
    KEYBOARD_ACTIVATE,
    KEYBOARD_DEACTIVATE,
    MOUSE_MOVE_ACTIVATE,
    MOUSE_MOVE_DEACTIVATE,
    MOUSE_CLICK_ACTIVATE,
    MOUSE_CLICK_DEACTIVATE,
    DISCONNECT,
    PAUSE,
    UNPAUSE,
    FREQUENCY,
    STATUS,

    //Các trả lời hợp lệ
    VALID_INPUT_KEYBOARD = 200,   // data / INPUT_DATA Response - KeystrokeData
    VALID_INPUT_MOUSE,            // data / INPUT_DATA Response - MouseData
    VALID_PING,                   // None
    VALID_USER,                   // String
    VALID_KEYBOARD_ACTIVATE,      // None
    VALID_KEYBOARD_DEACTIVATE,    // None
    VALID_MOUSE_MOVE_ACTIVATE,    // None
    VALID_MOUSE_MOVE_DEACTIVATE,  // None
    VALID_MOUSE_CLICK_ACTIVATE,   // None
    VALID_MOUSE_CLICK_DEACTIVATE, // None
    VALID_DISCONNECT,             // None
    VALID_PAUSE,                  // None
    VALID_UNPAUSE,                // None
    VALID_FREQUENCY,              // None
    VALID_STATUS,                 // cấu trúc StatusData

    //Error codes
     INVALID_INPUT_DATA = 400,
    INVALID_PING,
    INVALID_USER,
    INVALID_KEYBOARD_ACTIVATE,
    INVALID_KEYBOARD_DEACTIVATE,
    INVALID_MOUSE_MOVE_ACTIVATE,
    INVALID_MOUSE_MOVE_DEACTIVATE,
    INVALID_MOUSE_CLICK_ACTIVATE,
    INVALID_MOUSE_CLICK_DEACTIVATE,
    INVALID_DISCONNECT,
    INVALID_PAUSE,
    INVALID_UNPAUSE,
    INVALID_FREQUENCY,
    INVALID_STATUS

};

#endif /* ENUMREQUESTSTYPES_HPP_ */