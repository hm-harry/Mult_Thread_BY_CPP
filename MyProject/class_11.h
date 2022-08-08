#pragma once
#include<iostream>
#include<thread>
#include<mutex>
#include<future>

using namespace std;
// һ��ԭ�Ӳ��������++ -- += &= != ^=��֧�ֵ�
// std::async��̸
atomic<int> g_mycount = 0;

//void mythread() {
//	for (int i = 0; i < 100000; i++) {
//		g_mycount++;
//		//g_mycount = g_mycount + 1; // ��֧��
//	}
//}

int mythread() {
	this_thread::sleep_for(5s);
	cout << "mythread() start thread id = " << this_thread::get_id() << endl;
	
	return 1;
}

void class_11() {
	cout << "main() start thread id = " << this_thread::get_id() << endl;
	shared_future<int> result = async(&mythread); // launch::deferred(�ӳٵ��ã��ӳٵ�.get()��.wait()���Ҳ��������߳�) launch::async(ǿ�ƴ���һ���߳�)������һ���첽���� Ĭ�����Լ�ѡ��
	future_status status = result.wait_for(0s); //(chrono::seconds(0));
	if (status == future_status::deferred) {
		cout << result.get() << endl;
	}
	else {
		if (status == future_status::ready) {
			cout << result.get() << endl;
		}
		else {
			cout << "�̳߳�ʱ" << endl;
			cout << result.get() << endl;
		}
	}
	cout << result.get() << endl;
	
	cout << "hello world" << endl;
}