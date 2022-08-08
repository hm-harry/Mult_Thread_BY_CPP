#pragma once
#include<iostream>
#include<thread>
#include<mutex>
#include<future>
#include<list>

using namespace std;
// ��ٻ��� wait() notify_one() notify_all()     wait��Ҫ�еڶ�������һ����lambda���ʽ
atomic<int> atm = 0;
class A {
public:
	/*void inMsgRecvQueue() {
		for (int i = 0; i < 1000; i++) {
			unique_lock<mutex> sbguard1(my_mutex1, defer_lock);
			if (sbguard1.try_lock() == true) {
				cout << "inMsgRecvQueue�߳� ����һ��Ԫ��" << i << endl;
				msgRecvQueue.push_back(i);
				my_cond.notify_one();
				sbguard1.unlock();
			}
			else
			{
				cout << "inMsgRecvQueueִ�У���û���õ��������Ըɱ����" << endl;
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
				cout << "outMsgRecvQueue�߳� ȡ��һ��Ԫ��" << command << endl;
				sbguard1.unlock();
			}
			else
			{
				cout << "outMsgRecvQueueִ�У���û���õ��������Ըɱ����" << endl;
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
	mutex my_mutex1;//����һ��������
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