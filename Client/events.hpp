#ifndef EVENTS_HPP_
#define EVENTS_HPP_

#include <windows.h>
#include <winuser.h>
#include <string>

//	For storing array structure of multiple keys
struct MULKEY {
	int vKey;
};

#define MAXKEY 10
class Event {
	public:
	// Hàm để mô phỏng một sự kiện bàn phím cho một phím duy nhất
		int kbtEventSimulate(SHORT vKey);
		// Hàm để mô phỏng một sự kiện bàn phím cho nhiều phím
		int kbtEventSimulateMul(struct MULKEY vKeys[MAXKEY], int len, char ch);
		// Hàm để mô phỏng sự kiện di chuyển chuột
		int mouseEventSimulateMov(LONG x, LONG y);
		// Hàm để mô phỏng sự kiện click chuột
		int mouseEventSimulateClick(int rol);
		// Hàm để lấy mã phím ảo cho một ký tự nhất định
		int GetKeyCode(char *k);
};


/*
enum mouse { 
			 leftClick, 
			 rightClick
		   }; 

*/

#define BACK VK_BACK
#define ENTER VK_RETURN
#define SHIFT VK_SHIFT
#define CTRL VK_CONTROL
#define ALT VK_MENU
#define CAPS VK_CAPITAL
#define ESC VK_ESCAPE
#define PUP VK_PRIOR
#define PDOWN VK_NEXT
#define END VK_END
#define HOME VK_HOME
#define LEFT VK_LEFT
#define UP VK_UP
#define RIGHT VK_RIGHT
#define DOWN VK_DOWN
#define PRINTSCRN VK_SNAPSHOT
#define INSERT VK_INSERT
#define DEL_KEY VK_DELETE
#define WIN VK_LWIN

#endif /*EVENTS_HPP_*/
