#pragma once
#include<iostream>
#include<thread>

using namespace std;

void MyPrint() {
	cout << "MyPrint start" << endl;
	cout << "MyPrint finish" << endl;
}

class TA {
public:
	TA(int i):m_i(i) {
		cout << "TA()���캯��" << endl;
	}
	TA(const TA &ta) :m_i(ta.m_i){
		cout << "�������캯��" << endl;
	}
	~TA() {
		cout << "��������" << endl;
	}
	void operator() (){
		cout << "m_i = " << m_i << endl;//����Ԥ�ϵĺ��
		cout << "m_i = " << m_i << endl;
		cout << "m_i = " << m_i << endl;
		cout << "m_i = " << m_i << endl;
	}
private:
	int m_i;
};

void class_2() {
	// ���������Ƿ�ִ����ı�־�����߳��Ƿ�ִ����
	// ��ʱ��һ����������߳̽�������������ӽ��̻�û��ִ����ϣ�����Щ�ӽ��̻ᱻǿ����ֹ
	// thread��һ����
	// thread mytobj(MyPrint);
	// mytobj.join();

	// ���߳̿�ʼִ��
	//thread* mytobj = new thread(MyPrint);

	// �������̲߳��ȴ����߳̽�����
	// mytobj->join();
	
	// ���� ���ص����߳̽��������߳̿����Ƚ��� (������ʹ��)   ����ʱ���Զ��ͷ�    �ػ��߳�
	// mytobj->detach();

	// �ж��ܲ���join ����true��false
	/*if (mytobj->joinable()) {
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}*/

	int myi = 6;
	 TA* ta = new TA(myi);
	 thread mytobj2(*ta);
	  mytobj2.join();
	 // mytobj2.detach();

	//auto mylamthread = [=](){
	//	cout << "lamda�߳�" << endl;
	//};
	//thread mytobj3(mylamthread);
	//// mytobj3.join();
	//mytobj3.detach();

	cout << "hello world" << endl;
}