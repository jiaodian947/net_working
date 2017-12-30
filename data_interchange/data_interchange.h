#ifndef DATA_INTERCHANGE_H
#define DATA_INTERCHANGE_H

#include <WinSock2.h>
#pragma comment(lib, "WS2_32") 
#include <mswsock.h>
 
class DataInterChange
{
public:
	DataInterChange();
	~DataInterChange();

	// 初始化io
	bool IniWinSocket();

	// 创建监听
	int CreateListener(const char* addr, int port);

	// 接受消息
	int LoopEventInfo();

	// 投递接收事件
	int PutAccpet();

	// 投递一个接受消息的事件
	int PutReceve(SOCKET& socket_handle, SOCKET& listen_socket_handle);

private:

	//完成端口句柄 
	void* completion_handle_;	
	SOCKET listenSocket;


	LPFN_ACCEPTEX lpfn_accept_ex_;
	LPFN_GETACCEPTEXSOCKADDRS lpfn_get_acceptex_sock_addrs_;

};
#endif