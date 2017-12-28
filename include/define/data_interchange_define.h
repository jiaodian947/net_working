#ifndef DATA_INTERCHANGE_DEFINE_H
#define DATA_INTERCHANGE_DEFINE_H

// 完成端口类型
enum COMPLETION_PORT_TYPE
{
	COMPLETION_PORT_NONE,				// 无类型，可以用来删除		
	COMPLETION_PORT_LISTENER			// 监听类型
};

typedef struct overlapp_sct
{
	OVERLAPPED overlapp;
	int overlapp_type;
	char buf[256];

}overlapp_sct;
#endif