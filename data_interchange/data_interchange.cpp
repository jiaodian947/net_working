
#include "data_interchange.h"
#include <singleton_temp.h>
#include <data_interchange_define.h>
#include "socket_Tool.h"
#include <mswsock.h>


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

	if (!SetBroadcast(socket))
	{
		return 0;
	}

	if (!ListenSocket(socket, SOMAXCONN))
	{
		return 0;
	}

	LPFN_ACCEPTEX lpfnAcceptEx = NULL;
	LPFN_GETACCEPTEXSOCKADDRS lpfnGetAcceptExSockaddrs = NULL;
	GUID GuidAcceptEx = WSAID_ACCEPTEX;
	GUID GuidGetAcceptExSockaddrs = WSAID_GETACCEPTEXSOCKADDRS;
	DWORD dwIoctlBytes;

	WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidAcceptEx,
		sizeof(GuidAcceptEx), &lpfnAcceptEx, sizeof(lpfnAcceptEx),
		&dwIoctlBytes, NULL, NULL);
	WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidGetAcceptExSockaddrs, sizeof(GuidGetAcceptExSockaddrs),
		&lpfnGetAcceptExSockaddrs, sizeof(lpfnGetAcceptExSockaddrs),
		&dwIoctlBytes, NULL, NULL);

	lpfn_accept_ex_= lpfnAcceptEx;
	lpfn_get_acceptex_sock_addrs_ = lpfnGetAcceptExSockaddrs;

	for (size_t i = 0; i < 10; ++i)
	{
		SOCKET accept_sock;

		if (!GetSocket(accept_sock))
		{
			return -1;
		}

		// ready to accept
		overlapp_sct pOverlapPlus;
		DWORD dwBytes;

		if (!lpfnAcceptEx(socket, accept_sock,
			pOverlapPlus.buf, 0,
			sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &dwBytes,
			&pOverlapPlus.overlapp))
		{
			int err = WSAGetLastError();

			if (err != WSA_IO_PENDING)
			{
				SocketClose(accept_sock);
				return -1;
			}
		}
	}

	return 0;
}

int DataInterChange::GetEventInfo()
{
	DWORD count;
	OVERLAPPED *overlapp = NULL;
	int index;
	while (1)
	{
		if (GetQueuedCompletionStatus(completion_handle_, &count, (PULONG_PTR)&index, &overlapp, INFINITE))  //第三个lpCompletionKey参数不能填null，可以随意填写一个结构体进去，如果是null不管怎么这个函数都不会阻塞；
		{
			overlapp_sct* pIoContext = (overlapp_sct*)overlapp;
			switch (index)
			{
			case COMPLETION_PORT_LISTENER:
			{
				
			}
			break;
			case COMPLETION_PORT_ACCPTE:
			{

			}
				break;
			}
		}
	}

	return 0;
}

int DataInterChange::PutAccpet()
{

}
