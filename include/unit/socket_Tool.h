#ifndef DEF_SOCKETDEFINE
#define DEF_SOCKETDEFINE

#include <WinSock2.h>
#include <windows.h>
#include <queue>
#pragma comment(lib, "WS2_32.lib") 

inline bool GetSocket(SOCKET& socket_handle)
{
	socket_handle = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == socket_handle)
	{
		return false;
	}

	return true;
}

inline bool SetBroadcast(SOCKET& socket_handle)
{
	// 设置socket可重用
	int bReuseaddr = 1;
	int ret = setsockopt(socket_handle, SOL_SOCKET, SO_REUSEADDR, (const char*)&bReuseaddr, sizeof(bReuseaddr));
	if (SOCKET_ERROR == ret)
	{
		return false;
	}

	return true;
}

inline bool BingSocket(SOCKET& socket_handle, const char* addr, int port)
{
	sockaddr_in sa;
	sa.sin_family = AF_INET;
	// 监听所有地址就填0.0.0.0和ADDR_ANY一样的结果
	sa.sin_addr.s_addr = inet_addr(addr);
	sa.sin_port = htons((u_short)port);

	int res = bind(socket_handle, (const sockaddr*)&sa, sizeof(sa));
	if (SOCKET_ERROR == res)
	{
		return false;
	}
	return true;
}

inline bool ListenSocket(SOCKET& socket_handle, int backlog)
{
	int res = listen(socket_handle, SOMAXCONN_HINT(backlog));
	if (SOCKET_ERROR == res)
	{
		return false;
	}

	return true;
}

inline bool SocketClose(SOCKET& sock_handle)
{
	int res = closesocket(sock_handle);
	if (SOCKET_ERROR == res)
	{
		return false;
	}

	return true;
}
#endif // !DEF_SOCKETDEFINE