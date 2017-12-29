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

	// ��ʼ��io
	bool IniWinSocket();

	// ��������
	int CreateListener(const char* addr, int port);

	// ������Ϣ
	int GetEventInfo();

	int PutAccpet();

private:

	//��ɶ˿ھ�� 
	void* completion_handle_;	

	LPFN_ACCEPTEX lpfn_accept_ex_;
	LPFN_GETACCEPTEXSOCKADDRS lpfn_get_acceptex_sock_addrs_;

};
#endif