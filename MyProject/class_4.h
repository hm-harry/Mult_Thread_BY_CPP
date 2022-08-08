#pragma once
#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>
using namespace std;

//vector<int> g_v = { 1, 2, 3 }; 
//
////�߳���ں���
//void myprint(int inum) {
//	/*cout << "myprint�߳̿�ʼִ����" << inum << endl;
//
//	cout << "myprint�߳̽�����" << inum << endl;*/
//
//	cout << inum << " id = " << this_thread::get_id() << " gv = " << g_v[0] << g_v[1] << g_v[2] << endl;
//}

class A {
public:
	std::unique_lock<mutex> rtn_unique_lock() {
		std::unique_lock<mutex> tmpguard(my_mutex1);
		return tmpguard;
	}
	// �ռ��������
	void inMsgRecvQueue() {
		for (int i = 0; i < 1000; i++) {

			/*lock_guard<mutex> lock1(my_mutex1);
			lock_guard<mutex> lock2(my_mutex2);*/

			/*my_mutex1.lock();
			my_mutex2.lock();*/

			// lock(my_mutex1, my_mutex2);

			// lock_guard<mutex> lock1(my_mutex1, adopt_lock);
			// lock_guard<mutex> lock2(my_mutex2, adopt_lock);//adopt_lock�������

			// my_mutex1.lock();
			// unique_lock<mutex> sbguard1(my_mutex1, adopt_lock);// adopt_lock������� ����ѻ�������ǰlock ֪ͨ����Ҫ����lock

			// unique_lock<mutex> sbguard1(my_mutex1, try_to_lock);//try_to_lock ֮ǰǧ������֮ǰlock

			//unique_lock<mutex> sbguard1(my_mutex1, defer_lock);//defer_lock ֮ǰǧ������֮ǰlock ��û�и�mutex ����
			//sbguard1.lock(); // �����Լ�unlock
			////......//���������
			//sbguard1.unlock();
			////......//����ǹ������
			//sbguard1.lock();
			////......//���������

			unique_lock<mutex> sbguard1(my_mutex1, defer_lock);
			// mutex *ptx = sbguard1.release(); //��� 
			//if (sbguard1.owns_lock()) {
			if (sbguard1.try_lock() == true) {
				cout << "1����һ��Ԫ��" << i << endl;
				msgRecvQueue.push_back(i);
			}
			else
			{
				cout << "1inMsgRecvQueueִ�У���û���õ��������Ըɱ����" << endl;
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
	//��Ϣ������ȥ������
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
				cout << "2δ��ȡ������" << endl;
			}

		}
	}

private:
	list<int> msgRecvQueue;
	mutex my_mutex1;//����һ��������
					//mutex my_mutex2;//����һ��������
};

void class_4() {
	// �����͵ȴ�����߳�
	// ����߳�ִ��˳�����ҵ�  
	// ֻ�������ǰ�ȫ�ȶ���
	//�ж���д�� ��Ҫ���������� ����ͬʱд������ͬʱ��
	/*vector<thread> mythreads;
	for (int i = 0; i < 10; i++) {
	mythreads.push_back(thread(&myprint, i));
	}
	for (vector<thread>::iterator it = mythreads.begin(); it != mythreads.end(); it++) {
	(*it).join();
	}*/

	// ���������̱߳���������������ĸ���������� mutex ��һ������� ���� lock()
	// lock() unlock() ��lock() ������������ unlock()
	// lock() unlock() �ɶ�ʹ��!!!!!
	// Ϊ�˷�ֹ���� ��lock_guard()
	// ���� ����������������������
	// lock()����ģ�� һ���������������������ϻ����� �������������� Ҫô��������ס Ҫô��û��ס

	// ��unique_lockȡ��lock_guard ����һ����lock_guard
	A myobj;
	thread myInMsgObj(&A::inMsgRecvQueue, &(myobj));
	thread myOutMsgObj(&A::outMsgRevQueue, &(myobj));

	myInMsgObj.join();
	myOutMsgObj.join();

	cout << "hello world" << endl;
}