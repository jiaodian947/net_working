#ifndef DEF_SOCKETDEFINE
#define DEF_SOCKETDEFINE

#include <WinSock2.h>
#include <windows.h>
#include <queue>
#pragma comment(lib, "WS2_32.lib") 

//��Socket�س�ʼ����ʱ�������Ϊ0Ĭ�ϳ�ʼ����
#define DEF_SOCKETNUM 1000

typedef struct _SSOCKET
{
	SOCKET sSocket;
	int Flag;
	_SSOCKET()
	{
		sSocket = socket(AF_INET, SOCK_STREAM, 0);
	}
} SSOCKET;

#endif // !DEF_SOCKETDEFINE