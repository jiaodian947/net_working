#ifndef DATA_INTERCHANGE_H
#define DATA_INTERCHANGE_H

class DataInterChange
{
public:
	DataInterChange();
	~DataInterChange();

	// ��ʼ��io
	bool IniWinSocket();

	// ��������
	int CreateListener(const char* addr, int port);
private:
	void* completion_handle_;	//��ɶ˿ھ�� 

};
#endif