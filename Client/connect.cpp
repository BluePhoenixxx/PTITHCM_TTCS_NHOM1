#include "connect.hpp"

SOCKET ConnectServer(char *host, char *port)
{
	// Tạo một cấu trúc addrinfo để chứa thông tin kết nối
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));

	// Đặt loại socket thành TCP
	hints.ai_socktype = SOCK_STREAM; // Socket TCP

	// Con trỏ để lưu địa chỉ server được giải quyết
	struct addrinfo *srvAddr;

	// Giải quyết địa chỉ server
	if (getaddrinfo(host, port, &hints, &srvAddr))
		return -1; // Trả về -1 nếu việc giải quyết địa chỉ thất bại

	// Tạo socket kết nối
	SOCKET peerSocket;
	peerSocket = socket(srvAddr->ai_family, srvAddr->ai_socktype, srvAddr->ai_protocol);
	if (peerSocket == INVALID_SOCKET)
		return -1; // Trả về -1 nếu tạo socket thất bại

	// Kết nối đến server
	if (connect(peerSocket, srvAddr->ai_addr, srvAddr->ai_addrlen))
		return -1; // Trả về -1 nếu kết nối thất bại

	// Trả về số tham chiếu socket nếu kết nối thành công
	return peerSocket;
}

bool SendData(SOCKET fd, char *data)
{
	if (send(fd, data, strlen(data), 0) < 1)
		return false;
	return 0;
}

void SendSuccess(int fd)
{
	char msg[10] = "Success!!";
	SendData(fd, msg);
}

void SendUnsuccess(int fd)
{
	char msg[14] = "Unsuccess!!";
	SendData(fd, msg);
}
