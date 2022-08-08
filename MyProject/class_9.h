#pragma once
#include<iostream>
#include<thread>
#include<future>
using namespace std;

// std::async��һ������ģ�� ����һ���첽���� ����һ��future ������future�����get����
// ������async()����һ������������������launch���ͣ�ö������,             �̵߳�����get()����wait()���ò�ִ��,�ӳٵ���,����û�����̴߳�������     launch::deferred    launch::asyncϵͳĬ��
// packaged_task�������,
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
	//std::future<int> result = std::async(launch::async,&A::mythread, &a, tmpoar); // ����һ���̲߳���ʼִ��
	////std::future<int> result = std::async(&mythread, tmpoar);
	//cout << "continue..." << endl;
	//int def;
	//def = 0;
	//cout << result.get() << endl; // ���̷߳��� ���õ�ֵ�Ϳ�ס
	////result.wait();// ������ֵ
	//cout << "hello world" << endl;

	//cout << "main" << "thread id = " << this_thread::get_id() << endl;
	//packaged_task<int(int)>mypt1(mythread); // �Ѻ���mythreadͨ��package_task��װ����
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
	//myptTmp(1); // ֱ�ӵ��ã��൱�ں������� û�д������߳�
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