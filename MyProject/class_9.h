#pragma once
#include<iostream>
#include<thread>
#include<future>
using namespace std;

// std::async是一个函数模板 启动一个异步任务 返回一个future 可以用future对象的get函数
// 额外向async()传递一个参数，参数类型是launch类型，枚举类型,             线程到后面get()或者wait()调用才执行,延迟调用,并且没有新线程创建出来     launch::deferred    launch::async系统默认
// packaged_task打包任务,
// promise

//class A {
//public:
//	int mythread(int mypar) {
//		cout << mypar << endl;
//		cout << "mythread() start " << "thread id = " << this_thread::get_id() << endl;
//		chrono::milliseconds dura(5000);
//		this_thread::sleep_for(dura);
//		cout << "mythread() end " << "thread id = " << this_thread::get_id() << endl;
//		return 5;
//	}
//
//};

//int mythread(int mypar) {
//	cout << mypar << endl;
//	cout << "mythread() start " << "thread id = " << this_thread::get_id() << endl;
//	chrono::milliseconds dura(5000);
//	this_thread::sleep_for(dura);
//	cout << "mythread() end " << "thread id = " << this_thread::get_id() << endl;
//	return 5;
//}
//
//vector<packaged_task<int(int)>> mytasks;

void mythread(std::promise<int> &tmp, int cale) {
	cale++;
	chrono::milliseconds dura(5000);
	this_thread::sleep_for(dura);

	int result = cale;
	tmp.set_value(result);
}

void mythread2(std::future<int> &tmp) {
	auto result = tmp.get();
	cout << "mythread2 result = " << result << endl;
}

void class_9() {
	//A a;
	//int tmpoar = 12;
	//cout << "main" << "thread id = " << this_thread::get_id() << endl;
	//std::future<int> result = std::async(launch::async,&A::mythread, &a, tmpoar); // 创造一个线程并开始执行
	////std::future<int> result = std::async(&mythread, tmpoar);
	//cout << "continue..." << endl;
	//int def;
	//def = 0;
	//cout << result.get() << endl; // 等线程返回 不拿到值就卡住
	////result.wait();// 不返回值
	//cout << "hello world" << endl;

	//cout << "main" << "thread id = " << this_thread::get_id() << endl;
	//packaged_task<int(int)>mypt1(mythread); // 把函数mythread通过package_task包装起来
	//packaged_task<int(int)>mypt2([=](int mypar) {
	//	cout << mypar << endl;
	//	cout << "mythread() start " << "thread id = " << this_thread::get_id() << endl;
	//	chrono::milliseconds dura(5000);
	//	this_thread::sleep_for(dura);
	//	cout << "mythread() end " << "thread id = " << this_thread::get_id() << endl;
	//	return 5;
	//});
	//mytasks.push_back(move(mypt1));
	//mytasks.push_back(move(mypt2));
	//packaged_task<int(int)> myptTmp;
	//vector<packaged_task<int(int)>>::iterator it = mytasks.begin();
	//mytasks.erase(it);
	//myptTmp = move(*it);
	//myptTmp(1); // 直接调用，相当于函数调用 没有创建子线程
	///*thread t1(ref(mypt), 1);
	//t1.join();*/
	//future<int> result = myptTmp.get_future();
	//cout << result.get() << endl;
	//cout << "hello world" << endl;

	promise<int> mypromise;
	thread t1(&mythread, ref(mypromise), 1);
	t1.join();
	future<int> result = mypromise.get_future();
	//cout << result.get() << endl;
	thread t2(&mythread2, ref(result));
	t2.join();
	cout << "hello world" << endl;
}