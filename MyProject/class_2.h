#pragma once
#include<iostream>
#include<thread>

using namespace std;

void MyPrint() {
	cout << "MyPrint start" << endl;
	cout << "MyPrint finish" << endl;
}

class TA {
public:
	TA(int i):m_i(i) {
		cout << "TA()构造函数" << endl;
	}
	TA(const TA &ta) :m_i(ta.m_i){
		cout << "拷贝构造函数" << endl;
	}
	~TA() {
		cout << "析构函数" << endl;
	}
	void operator() (){
		cout << "m_i = " << m_i << endl;//不可预料的后果
		cout << "m_i = " << m_i << endl;
		cout << "m_i = " << m_i << endl;
		cout << "m_i = " << m_i << endl;
	}
private:
	int m_i;
};

void class_2() {
	// 整个进程是否执行完的标志是主线程是否执行完
	// 此时，一般情况，主线程结束，如果其他子进程还没有执行完毕，那这些子进程会被强行终止
	// thread是一个类
	// thread mytobj(MyPrint);
	// mytobj.join();

	// 子线程开始执行
	//thread* mytobj = new thread(MyPrint);

	// 阻塞主线程并等待子线程进行完
	// mytobj->join();
	
	// 分离 不必等子线程结束，主线程可以先结束 (不建议使用)   运行时库自动释放    守护线程
	// mytobj->detach();

	// 判断能不能join 返回true和false
	/*if (mytobj->joinable()) {
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}*/

	int myi = 6;
	 TA* ta = new TA(myi);
	 thread mytobj2(*ta);
	  mytobj2.join();
	 // mytobj2.detach();

	//auto mylamthread = [=](){
	//	cout << "lamda线程" << endl;
	//};
	//thread mytobj3(mylamthread);
	//// mytobj3.join();
	//mytobj3.detach();

	cout << "hello world" << endl;
}