/*********************************
/* author: 			janstring
/* file:			SingletonTemp.h
/* CreatDate: 		2017/05/14 14:47
/* modify:			nobody
/* LastModifyData:	2017/05/14 14:47
/* brief: 			����ģʽ����ģ����
/* TODO:
/*********************************/
#ifndef SINGLETONREMP_H
#define SINGLETONREMP_H

#define DEF_SINGLETON(P) friend class SingletonTemp<P>

template<class T>
class SingletonTemp
{

protected:
	SingletonTemp() {}
	~SingletonTemp() {}
	//���ø�ֵ����
	T &operator=(const T&) {}

protected:
	static T* Instance;
public:
	static T& GetInstance()
	{
		return *Instance
	}

private:
	class Garbo
	{
	public:
		~Garbo()
		{
			if (NULL != SingletonTemp<T>::Instance)
			{
				delete SingletonTemp<T>::Instance;
				SingletonTemp<T>::Instance = NULL;
			}
		}

	};
	static Garbo garbo;

};

//����ģʽ������̬������ʼ����ʱ���ֱ�ӷ����ڴ�
template<class T>
T* SingletonTemp<T>::Instance = new T;

#endif //SINGLETONREMP_H