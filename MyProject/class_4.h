#pragma once
#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>
using namespace std;

//vector<int> g_v = { 1, 2, 3 }; 
//
////线程入口函数
//void myprint(int inum) {
//	/*cout << "myprint线程开始执行了" << inum << endl;
//
//	cout << "myprint线程结束了" << inum << endl;*/
//
//	cout << inum << " id = " << this_thread::get_id() << " gv = " << g_v[0] << g_v[1] << g_v[2] << endl;
//}

class A {
public:
	std::unique_lock<mutex> rtn_unique_lock() {
		std::unique_lock<mutex> tmpguard(my_mutex1);
		return tmpguard;
	}
	// 收集玩家数据
	void inMsgRecvQueue() {
		for (int i = 0; i < 1000; i++) {

			/*lock_guard<mutex> lock1(my_mutex1);
			lock_guard<mutex> lock2(my_mutex2);*/

			/*my_mutex1.lock();
			my_mutex2.lock();*/

			// lock(my_mutex1, my_mutex2);

			// lock_guard<mutex> lock1(my_mutex1, adopt_lock);
			// lock_guard<mutex> lock2(my_mutex2, adopt_lock);//adopt_lock标记作用

			// my_mutex1.lock();
			// unique_lock<mutex> sbguard1(my_mutex1, adopt_lock);// adopt_lock标记作用 必须把互斥量提前lock 通知不需要构造lock

			// unique_lock<mutex> sbguard1(my_mutex1, try_to_lock);//try_to_lock 之前千万不能在之前lock

			//unique_lock<mutex> sbguard1(my_mutex1, defer_lock);//defer_lock 之前千万不能在之前lock 并没有给mutex 加锁
			//sbguard1.lock(); // 不用自己unlock
			////......//处理共享代码
			//sbguard1.unlock();
			////......//处理非共享代码
			//sbguard1.lock();
			////......//处理共享代码

			unique_lock<mutex> sbguard1(my_mutex1, defer_lock);
			// mutex *ptx = sbguard1.release(); //解绑 
			//if (sbguard1.owns_lock()) {
			if (sbguard1.try_lock() == true) {
				cout << "1插入一个元素" << i << endl;
				msgRecvQueue.push_back(i);
			}
			else
			{
				cout << "1inMsgRecvQueue执行，但没有拿到锁，可以干别的事" << endl;
			}
			// ptx->unlock();

			//my_mutex1.unlock();
			//my_mutex2.unlock();
		}
	}

	bool outMsgLULProc(int &command) {
		// lock_guard<mutex> sbguard(my_mutex);

		/*lock_guard<mutex> lock2(my_mutex2);
		lock_guard<mutex> lock1(my_mutex1);*/


		//unique_lock<mutex> sbguard1(my_mutex1);
		//unique_lock<mutex> sbguard2(move(sbguard1));
		unique_lock<mutex> sbguard1 = rtn_unique_lock();
		// std::chrono::milliseconds dura(200); //200ms
		// std::this_thread::sleep_for(dura);

		if (msgRecvQueue.empty()) {
			cout << "2" << endl;
			return false;
		}
		else {
			cout << "22" << endl;
			command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			return true;
		}
	}
	//消息队列里去除数据
	void outMsgRevQueue() {
		int command = 0;
		for (int i = 0; i < 100; i++)
		{
			/*my_mutex2.lock();
			my_mutex1.lock();*/
			// lock(my_mutex1, my_mutex2);

			bool result = outMsgLULProc(command);
			// my_mutex1.unlock();
			// my_mutex2.unlock();
			if (result) {
				cout << "2command = " << command << endl;
			}
			else {
				cout << "2未能取出数据" << endl;
			}

		}
	}

private:
	list<int> msgRecvQueue;
	mutex my_mutex1;//创建一个互斥量
					//mutex my_mutex2;//创建一个互斥量
};

void class_4() {
	// 创建和等待多个线程
	// 多个线程执行顺序是乱的  
	// 只读数据是安全稳定的
	//有读有写， 需要不崩溃处理， 不能同时写，不能同时读
	/*vector<thread> mythreads;
	for (int i = 0; i < 10; i++) {
	mythreads.push_back(thread(&myprint, i));
	}
	for (vector<thread>::iterator it = mythreads.begin(); it != mythreads.end(); it++) {
	(*it).join();
	}*/

	// 引入解决多线程保护共享数据问题的概念“互斥量” mutex 是一个类对象 加锁 lock()
	// lock() unlock() 先lock() 操作共享数据 unlock()
	// lock() unlock() 成对使用!!!!!
	// 为了防止遗忘 用lock_guard()
	// 死锁 至少两个互斥量才有死锁
	// lock()函数模板 一次锁上两个或者两个以上互斥量 不存在死锁问题 要么两个都锁住 要么都没锁住

	// 用unique_lock取代lock_guard 工作一般用lock_guard
	A myobj;
	thread myInMsgObj(&A::inMsgRecvQueue, &(myobj));
	thread myOutMsgObj(&A::outMsgRevQueue, &(myobj));

	myInMsgObj.join();
	myOutMsgObj.join();

	cout << "hello world" << endl;
}