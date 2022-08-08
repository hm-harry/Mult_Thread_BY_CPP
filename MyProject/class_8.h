#pragma once
#include<iostream>
#include<thread>
using namespace std;
#include<mutex>
#include<list>

//����������condition_variable

class A {
public:
	// �ռ��������
	void inMsgRecvQueue() {
		for (int i = 0; i < 1000; i++) {

			unique_lock<mutex> sbguard1(my_mutex1, defer_lock);
			// mutex *ptx = sbguard1.release(); //��� 
			//if (sbguard1.owns_lock()) {
			if (sbguard1.try_lock() == true) {
				cout << "1����һ��Ԫ��" << i << endl;
				msgRecvQueue.push_back(i);
				//my_cond.notify_one();
				my_cond.notify_all();
			}
			else
			{
				cout << "1inMsgRecvQueueִ�У���û���õ��������Ըɱ����" << endl;
			}
		}
	}

	void outMsgRevQueue() {
		int command = 0;
		while (true)
		{
			unique_lock<mutex> sbguard1(my_mutex1, defer_lock);
			sbguard1.lock();
			// wait �ǵ�һ������     �ڶ�����������ֵΪfalse��ôwait������������ ����������     ����������ĳ���̵߳���notify_one()Ϊֹ        �������true�ͷ���
			// ���waitû�еڶ������� ��ô�͸��ڶ�������lambda���ʽ����falseЧ��һ��         ����֮�����true
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
			cout << "outMsgRevQueueִ��" << "command = " << command << " thread id: " << this_thread::get_id() << endl;

			// ��ִ��һ��ʱ�� �ͻῨ���� ������Ч
		}
	}

private:
	list<int> msgRecvQueue;
	mutex my_mutex1;//����һ��������
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