#pragma once
#include<iostream>
#include<thread>
#include<mutex>
#include<future>
#include<list>

using namespace std;
// 虚假唤醒 wait() notify_one() notify_all()     wait中要有第二个参数一般是lambda表达式
atomic<int> atm = 0;
class A {
public:
	/*void inMsgRecvQueue() {
		for (int i = 0; i < 1000; i++) {
			unique_lock<mutex> sbguard1(my_mutex1, defer_lock);
			if (sbguard1.try_lock() == true) {
				cout << "inMsgRecvQueue线程 插入一个元素" << i << endl;
				msgRecvQueue.push_back(i);
				my_cond.notify_one();
				sbguard1.unlock();
			}
			else
			{
				cout << "inMsgRecvQueue执行，但没有拿到锁，可以干别的事" << endl;
			}
		}
	}

	void outMsgRecvQueue() {
		int command = 0;
		while (true) {
			unique_lock<mutex> sbguard1(my_mutex1, defer_lock);
			if (sbguard1.try_lock() == true) {
				my_cond.wait(sbguard1, [=]() {
					if (!msgRecvQueue.empty()) {
						return true;
					}
					else
					{
						return false;
					}
				});
				command = msgRecvQueue.front();
				msgRecvQueue.pop_front();
				cout << "outMsgRecvQueue线程 取出一个元素" << command << endl;
				sbguard1.unlock();
			}
			else
			{
				cout << "outMsgRecvQueue执行，但没有拿到锁，可以干别的事" << endl;
			}
		}
	}*/

	void inMsgRecvQueue() {
		for (int i = 0; i < 10000; i++) {
			atm++;
		}
	}

	void outMsgRecvQueue() {
		while (true) {
			cout << atm << endl;
		}
	}
private:
	list<int> msgRecvQueue;
	mutex my_mutex1;//创建一个互斥量
	condition_variable my_cond;

};

void class_13() {
	A myobja;
	thread myOutMsgObj(&A::outMsgRecvQueue, &(myobja));
	thread myInMsgObj(&A::inMsgRecvQueue, &(myobja));
	thread myInMsgObj2(&A::inMsgRecvQueue, &(myobja));

	myInMsgObj.join();
	myOutMsgObj.join();
	myInMsgObj2.join();
}