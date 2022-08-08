#pragma once
#include<iostream>
#include<thread>
#include<string>
using namespace std;
class A {
public:
	A(string a) :m_i(a) {
		cout << "���캯�� " << this << " threadID = " << this_thread::get_id() << endl;
	}
	A(const A &a) :m_i(a.m_i) {
		cout << "�������캯�� " << this << " threadID = " << this_thread::get_id() << endl;
	};
	void thread_work(int num) {
		cout << "���߳�thread_workִ��" << this << " threadID = " << this_thread::get_id() << endl;
	}
	void operator()(int num) {
		cout << "�ڽ�����ִ��" << this << " threadID = " << this_thread::get_id() << endl;
	}
	~A() {
		cout << "�������캯�� " << this << " threadID = " << this_thread::get_id() << endl;
	}
	string m_i;
};

void MyPrint(const int &i,unique_ptr<string> pmybuf){
	cout << i << endl;
	// pmybuf.m_i = "�����޸�";
	// cout << pmybuf.m_i << " MyPrint: " << this_thread::get_id() << endl; //ָ�����������
}

void class_3() {
	// ������ʱ������Ϊ���̲���
	cout << "���߳�id��" << this_thread::get_id() << endl;
	int mvar = 1;
	int &mvary = mvar;
	char mybuf[] = "this is a test";
	
	// std::ref�ؼ��� �����������ݵ�ַ û���ÿ�����������߳�
	// A* ac = new A(mybuf);
	// thread mytobj(MyPrint, mvary, std::ref(*ac));
	// cout << ac->m_i << endl;

	// unique_ptr<string> myp(new string("����ָ��"));
	// thread mytobj(MyPrint, mvary, std::move(myp));

	// A aa("���߳�");
	// thread mytobj(&A::thread_work, ref(aa), 15); // ref = &

	A aa("�ڽ�����");
	// thread mytobj(&A::operator(),&(aa), 15);
	thread mytobj(ref(aa), 15);
	 
	mytobj.join();
	// mytobj.detach();
	string a = "hello world";
	
	cout << a << endl;
}