#ifndef DATA_INTERCHANGE_DEFINE_H
#define DATA_INTERCHANGE_DEFINE_H

// ��ɶ˿�����
enum COMPLETION_PORT_TYPE
{
	COMPLETION_PORT_NONE,				// �����ͣ���������ɾ��		
	COMPLETION_PORT_LISTENER			// ��������
};

typedef struct overlapp_sct
{
	OVERLAPPED overlapp;
	int overlapp_type;
	char buf[256];

}overlapp_sct;
#endif