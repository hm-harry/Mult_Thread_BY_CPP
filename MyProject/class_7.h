#pragma once
#pragma once
#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
// 设计模式：项目开发模式 总结得到的
// 单例设计模式 ： 整个项目中有某个或者某些特殊的类 只能创建一个对象
// call_once()	功能能够保证函数a（）只被调用一次 具备互斥量能力  需要和一个标记结合使用 once_flag
std::mutex resource_mutex;
std::once_flag g_flag;

class MyCAS {
private:
	MyCAS() {}; //私有化构造函数

private:
	static MyCAS* m_instance;

public:
	static void CreateInstance() {
		chrono::milliseconds dura(5000);
		this_thread::sleep_for(dura);
		cout << "CreateInstance被执行了" << endl;
		m_instance = new MyCAS();
		static CGarhuishou c1;
	}

	static MyCAS* GetInstance() {
		// 提高效率
		if (m_instance == NULL) { //双重锁定
			unique_lock<mutex> mymutex(resource_mutex); //加锁是为了防止多线程重复初始化
			if (m_instance == NULL) {
				CreateInstance();
			}
		}

		/*std::call_once(g_flag, CreateInstance);
		cout << "call_once执行完了" << endl;*/
		return m_instance;
	}
	class CGarhuishou {
	public:
		~CGarhuishou() {
			if (MyCAS::m_instance) {
				delete MyCAS::m_instance;
				MyCAS::m_instance = NULL;
			}
		}
	};
	void func() {
		cout << "test" << endl;
	}
};

MyCAS* MyCAS::m_instance = NULL;// 静态变量类内声明 内外初始化

void mythread() {
	cout << "我的线程开始了" << endl;
	MyCAS* p_a = MyCAS::GetInstance();
	cout << "我的线程结束了" << endl;
}

void class_7() {
	//MyCAS* m_instance = MyCAS::GetInstance();
	// 可能面临GetInstance互斥
	//m_instance->func();
	//MyCAS::GetInstance()->func();
	//cout << MyCAS::GetInstance << " " << &MyCAS::GetInstance << endl;

	thread myobj1(mythread);
	thread myobj2(mythread);

	myobj1.join();
	myobj2.join();
}