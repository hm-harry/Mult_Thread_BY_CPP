#pragma once
#include<iostream>
#include<thread>
#include<string>
using namespace std;
class A {
public:
	A(string a) :m_i(a) {
		cout << "构造函数 " << this << " threadID = " << this_thread::get_id() << endl;
	}
	A(const A &a) :m_i(a.m_i) {
		cout << "拷贝构造函数 " << this << " threadID = " << this_thread::get_id() << endl;
	};
	void thread_work(int num) {
		cout << "子线程thread_work执行" << this << " threadID = " << this_thread::get_id() << endl;
	}
	void operator()(int num) {
		cout << "内建函数执行" << this << " threadID = " << this_thread::get_id() << endl;
	}
	~A() {
		cout << "析构构造函数 " << this << " threadID = " << this_thread::get_id() << endl;
	}
	string m_i;
};

void MyPrint(const int &i,unique_ptr<string> pmybuf){
	cout << i << endl;
	// pmybuf.m_i = "这里修改";
	// cout << pmybuf.m_i << " MyPrint: " << this_thread::get_id() << endl; //指针绝对有问题
}

void class_3() {
	// 传递临时对象作为进程参数
	cout << "主线程id：" << this_thread::get_id() << endl;
	int mvar = 1;
	int &mvary = mvar;
	char mybuf[] = "this is a test";
	
	// std::ref关键字 真正做到传递地址 没有用拷贝构造进入线程
	// A* ac = new A(mybuf);
	// thread mytobj(MyPrint, mvary, std::ref(*ac));
	// cout << ac->m_i << endl;

	// unique_ptr<string> myp(new string("智能指针"));
	// thread mytobj(MyPrint, mvary, std::move(myp));

	// A aa("子线程");
	// thread mytobj(&A::thread_work, ref(aa), 15); // ref = &

	A aa("内建函数");
	// thread mytobj(&A::operator(),&(aa), 15);
	thread mytobj(ref(aa), 15);
	 
	mytobj.join();
	// mytobj.detach();
	string a = "hello world";
	
	cout << a << endl;
}