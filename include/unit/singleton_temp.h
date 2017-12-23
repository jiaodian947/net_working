/*********************************
/* author: 			janstring
/* file:			SingletonTemp.h
/* CreatDate: 		2017/05/14 14:47
/* modify:			nobody
/* LastModifyData:	2017/05/14 14:47
/* brief: 			饿汉模式单例模板类
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
	//禁用赋值拷贝
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

//饿汉模式单例静态变量初始化的时候就直接分配内存
template<class T>
T* SingletonTemp<T>::Instance = new T;

#endif //SINGLETONREMP_H