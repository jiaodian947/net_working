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
	int GetEventInfo();

	int PutAccpet();

private:

	//完成端口句柄 
	void* completion_handle_;	

	LPFN_ACCEPTEX lpfn_accept_ex_;
	LPFN_GETACCEPTEXSOCKADDRS lpfn_get_acceptex_sock_addrs_;

};
#endif