
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
	if (!GetSocket(listenSocket))
	{
		return  0;
	}
	
	HANDLE handle = CreateIoCompletionPort((HANDLE)listenSocket, completion_handle_, COMPLETION_PORT_LISTENER, 0);
	if (handle != (HANDLE)completion_handle_)
	{
		return 0;
	}

	if (!BingSocket(listenSocket, addr, port))
	{
		return 0;
	}

	if (!SetBroadcast(listenSocket))
	{
		return 0;
	}

	if (!ListenSocket(listenSocket, SOMAXCONN))
	{
		return 0;
	}

	LPFN_ACCEPTEX lpfnAcceptEx = NULL;
	LPFN_GETACCEPTEXSOCKADDRS lpfnGetAcceptExSockaddrs = NULL;
	GUID GuidAcceptEx = WSAID_ACCEPTEX;
	GUID GuidGetAcceptExSockaddrs = WSAID_GETACCEPTEXSOCKADDRS;
	DWORD dwIoctlBytes;

	WSAIoctl(listenSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidAcceptEx,
		sizeof(GuidAcceptEx), &lpfnAcceptEx, sizeof(lpfnAcceptEx),
		&dwIoctlBytes, NULL, NULL);
	WSAIoctl(listenSocket, SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidGetAcceptExSockaddrs, sizeof(GuidGetAcceptExSockaddrs),
		&lpfnGetAcceptExSockaddrs, sizeof(lpfnGetAcceptExSockaddrs),
		&dwIoctlBytes, NULL, NULL);

	lpfn_accept_ex_= lpfnAcceptEx;
	lpfn_get_acceptex_sock_addrs_ = lpfnGetAcceptExSockaddrs;

	for (size_t i = 0; i < 10; ++i)
	{
		PutAccpet();
	}

	return 0;
}

int DataInterChange::LoopEventInfo()
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
				PutReceve(pIoContext->ConnectSocket, listenSocket);
				PutAccpet();
			}
			break;
			case COMPLETION_PORT_RECEV:
			{

				PutReceve(pIoContext->ConnectSocket, listenSocket);
			}
			break;
			}
		}
	}

	return 0;
}

int DataInterChange::PutAccpet()
{
	SOCKET accept_sock;

	if (!GetSocket(accept_sock))
	{
		return -1;
	}

	// ready to accept
	overlapp_sct* pOverlapPlus = new overlapp_sct;
	DWORD dwBytes;

	if (!lpfn_accept_ex_(listenSocket, accept_sock,
		pOverlapPlus->buf, 0,
		sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &dwBytes,
		&pOverlapPlus->overlapp))
	{
		int err = WSAGetLastError();

		if (err != WSA_IO_PENDING)
		{
			SocketClose(accept_sock);
			return -1;
		}
	}

	pOverlapPlus->ListenSocket = listenSocket;
	pOverlapPlus->ConnectSocket = accept_sock;

	return 0;
}

int DataInterChange::PutReceve(SOCKET& socket_handle, SOCKET& listen_socket_handle)
{
	HANDLE handle = CreateIoCompletionPort((HANDLE)socket_handle,
		(HANDLE)completion_handle_,
		(u_long)COMPLETION_PORT_RECEV, 0);

	overlapp_sct* pOverlapPlus = new overlapp_sct;
	pOverlapPlus->ConnectSocket = socket_handle;
	pOverlapPlus->ListenSocket = listenSocket;
	pOverlapPlus->overlapp_type = COMPLETION_PORT_RECEV;

	ULONG flags = 0;
	DWORD count;

	int res = WSARecv(socket_handle, &pOverlapPlus->buf, 1, &count, &flags,
		&pOverlapPlus->overlapp_type, NULL);

	if (SOCKET_ERROR == res)
	{
		int err = WSAGetLastError();

		if (err != WSA_IO_PENDING)
		{
			delete &pOverlapPlus;
			return false;
		}
	}

	return true;
}
