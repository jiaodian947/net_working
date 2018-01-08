
#include "data_interchange.h"
#include <singleton_temp.h>
#include <data_interchange_define.h>
#include "socket_Tool.h"


DataInterChange::DataInterChange()
{

}

DataInterChange::~DataInterChange()
{

}

bool DataInterChange::IniWinSocket()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return false;
	}

	return true;
}

int DataInterChange::CreateListener(const char* addr, int port)
{
	SOCKET socket;
	if (!GetSocket(socket))
	{
		return  0;
	}
	
	HANDLE handle = CreateIoCompletionPort((HANDLE)socket, completion_handle_, COMPLETION_PORT_LISTENER, 0);
	if (handle != (HANDLE)completion_handle_)
	{
		return 0;
	}

	if (!BingSocket(socket, addr, port))
	{
		return 0;
	}

	
}
