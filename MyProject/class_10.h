#pragma once
#include<iostream>
#include<thread>
#include<future>
#include<mutex>

using namespace std;

//future_status  timeout  ready  deferred
// shared_future 不仅仅是移动了  而是复制
// 原子操作 astomic


int mythread() {
	cout << "mythread() start" << " mythread id:" << this_thread::get_id() << endl;
	chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	cout << "mythread() end" << " mythread id:" << this_thread::get_id() << endl;
	return 5;
}

void mythread2(shared_future<int> &result) {
	cout << "mythread2() start" << " mythread2 id:" << this_thread::get_id() << endl;
	auto result1 = result.get();
	auto result2 = result.get();
	cout << result1 << endl;// get相当于移动语义
	cout << result2 << endl;// get相当于移动语义
	cout << "mythread2() end" << " mythread2 id:" << this_thread::get_id() << endl;
}

void class_10_1() {
	cout << "main " << "thread id = " << this_thread::get_id() << endl;
	/*future<int> result = async(launch::deferred, &mythread);*/
	//future<int> result = async(launch::deferred, &mythread);
	//cout << "continue......." << endl;
	//int def;
	//def = 0;
	//// cout << result.get() << endl;
	//future_status status = result.wait_for(std::chrono::seconds(6));
	//if (status == future_status::timeout) {// 线程超时
	//	cout << "超时了，线程还没执行完" << endl;
	//}
	//else if (status == future_status::ready) {// 线程成功返回
	//	cout << "线程成功返回" << endl;
	//	cout << result.get() << endl;
	//}
	//else if (status == future_status::deferred) {
	//	cout << "线程被延迟执行" << endl;
	//	cout << result.get() << endl; // 线程在这里执行

	//}

	packaged_task<int()> mypt(mythread);
	thread t1(ref(mypt));
	t1.join();
	//future<int> result = mypt.get_future();
	shared_future<int> result_s = mypt.get_future();
	//shared_future<int> result_s(move(result));
	/*bool ifcanget = result.valid();
	cout << int(ifcanget) << endl;
	shared_future<int> result_s(result.share());
	ifcanget = result.valid();
	cout << int(ifcanget) << endl;*/

	thread t2(&mythread2, ref(result_s));
	t2.join();

	cout << "main end" << endl;
}

// int g_mycount = 0;
//std::atomic<int> g_mycount = 0;
//std::mutex g_my_mutex;

//void mythread3() {
//	for (int i = 0; i < 10000000; ++i) {
//		// unique_lock<mutex> subgraud(g_my_mutex); //时间太长
//		g_mycount++;
//	}
//}

atomic<bool> g_ifend = false;
void mythread4() {
	chrono::seconds dure(1);
	this_thread::sleep_for(dure);
	while (g_ifend == false) {
		cout << "thread id = " << this_thread::get_id() << " 运行中 " << endl;
		this_thread::sleep_for(dure);
	}
	cout << "thread id = " << this_thread::get_id() << " 运行结束 " << endl;
}

void class_10_2() {
	//原子操作    互斥量：多线程中 保护共享数据   锁，操作共享数据，开锁
	// 有两个线程，对一个变量进行操作，一个线程读变量值，一个线程写变量值  

	//可以把原子操作理解成一种不需要互斥量加锁     原子操作针对的是一个变量，而不是一个代码段     不可分割的操作   要么完成 要么未完成
	// atomic 是一个类模板 用来封装某个值

	/*thread mytobj1(&mythread3);
	thread mytobj2(&mythread3);
	mytobj1.join();
	mytobj2.join();*/

	//cout << "end " << g_mycount << endl;


	g_ifend = true;
	thread mytobj1(&mythread4);
	thread mytobj2(&mythread4);
	chrono::seconds dure(5);
	this_thread::sleep_for(dure);
	
	mytobj1.join();
	mytobj2.join();
	cout << "end " << "main thread = " << this_thread::get_id() << endl;

}