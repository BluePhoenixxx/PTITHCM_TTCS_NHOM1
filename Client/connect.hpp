#ifndef CONNECT_HPP_
#define CONNECT_HPP

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")
// Hàm ConnectServer dùng để thiết lập kết nối tới một máy chủ.
SOCKET ConnectServer(char *host, char *port);
// Hàm SendData dùng để gửi dữ liệu qua kết nối đã thiết lập.
bool SendData(SOCKET fd, char *data);
// Hàm SendSuccess dùng để gửi thông báo thành công qua kết nối đã thiết lập.
void SendSuccess(int fd);
// Hàm SendUnsuccess dùng để gửi thông báo thất bại qua kết nối đã thiết lập.
void SendUnsuccess(int fd);

#endif /*CONNECT_HPP_*/
