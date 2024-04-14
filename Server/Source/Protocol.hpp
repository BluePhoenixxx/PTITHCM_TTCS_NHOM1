#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#include <cstdint>

namespace PTITKeyLogger {
    
    enum RequestCode: int32_t{
        /* Server yêu cầu*/
        PING = 0,
        ASK_ID,
        KEYBOARD_TRACK_ACTIVATE,
        KEYBOARD_TRACK_DEACTIVATE,
        MOUSE_MVMT_TRACK_ACTIVATE,
        MOUSE_MVMT_TRACK_DEACTIVATE,
        MOUSE_CLICK_TRACK_ACTIVATE,
        MOUSE_CLICK_TRACK_DEACTIVATE,
        DISCONNECT,
        PAUSE_ACTIVATE,
        PAUSE_DEACTIVATE,
        SET_FREQUENCY,
        GET_STATUS,

        /* Phản hồi thành công */
        VALID_KEY_EVENT = 200, /* Theo sau bởi 1 t_keyboard_event structure */
        VALID_MOUSE_EVENT,     /* Theo sau bởi 1 t_mouse_event structure */
        VALID_PING_RESPONSE,
        VALID_ASK_ID_RESPONSE, /* Theo sau bởi 1 t_client_id structure */
        VALID_KEYBOARD_TRACK_ACTIVATE,
        VALID_KEYBOARD_TRACK_DEACTIVATE,
        VALID_MOUSE_MVMT_TRACK_ACTIVATE,
        VALID_MOUSE_MVMT_TRACK_DEACTIVATE,
        VALID_MOUSE_CLICK_TRACK_ACTIVATE,
        VALID_MOUSE_CLICK_TRACK_DEACTIVATE,
        VALID_DISCONNECT,
        VALID_PAUSE_ACTIVATE,
        VALID_PAUSE_DEACTIVATE,
        VALID_SET_FREQUENCY,
        VALID_GET_STATUS_RESPONSE, /* Theo sau bởi 1 t_status structure */

        ERROR_PING = 400,
        ERROR_ASK_ID,
        ERROR_KEYBOARD_TRACK_ACTIVATE,
        ERROR_KEYBOARD_TRACK_DEACTIVATE,
        ERROR_MOUSE_MVMT_TRACK_ACTIVATE,
        ERROR_MOUSE_MVMT_TRACK_DEACTIVATE,
        ERROR_MOUSE_CLICK_TRACK_ACTIVATE,
        ERROR_MOUSE_CLICK_TRACK_DEACTIVATE,
        ERROR_DISCONNECT,
        ERROR_PAUSE_ACTIVATE,
        ERROR_PAUSE_DEACTIVATE,
        ERROR_SET_FREQUENCY,
        ERROR_GET_STATUS
    };

    enum ClickType : int32_t {NONE = 0, LEFT, RIGHT, OTHER }; // Định nghĩa enum cho mouse input

    struct t_client_id
    {
        char host[256];
        char user[256];
    };

    struct t_mouse_event
    {
        int32_t timestamp;
        char proc_name[256];
        int32_t pos_x;
        int32_t pos_y;
        ClickType click_type;
    };

    struct t_keyboard_event
    {
        int32_t timestamp;
        char proc_name[256];
        int32_t key;
    };

    struct t_status
    {
        bool keyboard_tracking;
        bool mouse_click_tracking;
        bool mouse_move_tracking;
        bool paused;
    };
    
} //Định nghĩa 1 namespace có tên là PTITKeyLogger

#endif /* !PROTOCOL_HPP_ */