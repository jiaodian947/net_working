#ifndef DATA_INTERCHANGE_H
#define DATA_INTERCHANGE_H

class DataInterChange
{
public:
	DataInterChange();
	~DataInterChange();

	// 初始化io
	bool IniWinSocket();

	// 创建监听
	int CreateListener(const char* addr, int port);
private:
	void* completion_handle_;	//完成端口句柄 

};
#endif