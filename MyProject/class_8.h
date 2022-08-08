#pragma once
#include<iostream>
#include<thread>
using namespace std;
#include<mutex>
#include<list>

//条件变量：condition_variable

class A {
public:
	// 收集玩家数据
	void inMsgRecvQueue() {
		for (int i = 0; i < 1000; i++) {

			unique_lock<mutex> sbguard1(my_mutex1, defer_lock);
			// mutex *ptx = sbguard1.release(); //解绑 
			//if (sbguard1.owns_lock()) {
			if (sbguard1.try_lock() == true) {
				cout << "1插入一个元素" << i << endl;
				msgRecvQueue.push_back(i);
				//my_cond.notify_one();
				my_cond.notify_all();
			}
			else
			{
				cout << "1inMsgRecvQueue执行，但没有拿到锁，可以干别的事" << endl;
			}
		}
	}

	void outMsgRevQueue() {
		int command = 0;
		while (true)
		{
			unique_lock<mutex> sbguard1(my_mutex1, defer_lock);
			sbguard1.lock();
			// wait 是等一个东西     第二个参数返回值为false那么wait将解锁互斥量 并阻塞本行     阻塞到其他某个线程调用notify_one()为止        如果返回true就放行
			// 如果wait没有第二个参数 那么就跟第二个参数lambda表达式返回false效果一样         唤醒之后就是true
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
			//sbguard1.unlock();
			cout << "outMsgRevQueue执行" << "command = " << command << " thread id: " << this_thread::get_id() << endl;

			// 若执行一段时间 就会卡在这 唤醒无效
		}
	}

private:
	list<int> msgRecvQueue;
	mutex my_mutex1;//创建一个互斥量
	condition_variable my_cond;
};

void class_8() {
	
	A myobj;
	thread myOutMsgObj(&A::outMsgRevQueue, &(myobj));
	thread myOutMsgObj2(&A::outMsgRevQueue, &(myobj));
	thread myInMsgObj(&A::inMsgRecvQueue, &(myobj));
	
	myOutMsgObj2.join();
	myInMsgObj.join();
	myOutMsgObj.join();
	

	cout << "hello world" << endl;
}