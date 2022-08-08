#pragma once
#include<iostream>
#include<thread>
#include<mutex>
#include<future>

using namespace std;
// 一般原子操作，针对++ -- += &= != ^=是支持的
// std::async详谈
atomic<int> g_mycount = 0;

//void mythread() {
//	for (int i = 0; i < 100000; i++) {
//		g_mycount++;
//		//g_mycount = g_mycount + 1; // 不支持
//	}
//}

int mythread() {
	this_thread::sleep_for(5s);
	cout << "mythread() start thread id = " << this_thread::get_id() << endl;
	
	return 1;
}

void class_11() {
	cout << "main() start thread id = " << this_thread::get_id() << endl;
	shared_future<int> result = async(&mythread); // launch::deferred(延迟调用，延迟到.get()和.wait()，且不创建新线程) launch::async(强制创建一个线程)（创建一个异步任务） 默认是自己选择
	future_status status = result.wait_for(0s); //(chrono::seconds(0));
	if (status == future_status::deferred) {
		cout << result.get() << endl;
	}
	else {
		if (status == future_status::ready) {
			cout << result.get() << endl;
		}
		else {
			cout << "线程超时" << endl;
			cout << result.get() << endl;
		}
	}
	cout << result.get() << endl;
	
	cout << "hello world" << endl;
}