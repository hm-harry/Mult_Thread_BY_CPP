#pragma once
#include<iostream>
#include<list>
#include<thread>
#include<future>
#include<mutex>
#include<Windows.h>

using namespace std;

//#define __WINDOWSJQ_
// windows�ٽ���    �����ν����ٽ���  �Զ�����
// �Զ�����windows�ٽ��� ����lock_guard<mutex>
// �ݹ�Ķ�ջ������recursive_mutex   �ܹ����lock  �ݹ����Ҳ������ ��Ӧ��û����
// timed_mutex����ʱ���ܵĵݹ��ջ������ try_lock_for() try_lock_until()
// recursive_timed_mutex
class CWinLock { //RAII��
public:
	CWinLock(CRITICAL_SECTION *pCritmp) {
		my_winsec = pCritmp;
		EnterCriticalSection(my_winsec);
	}
	~CWinLock() {
		LeaveCriticalSection(my_winsec);
	}
private:
	CRITICAL_SECTION *my_winsec;

};

class A {
public:
	void inMsgRecvQueue() {
		for (int i = 0; i < 5000; i++) {
			
#ifdef __WINDOWSJQ_
			// EnterCriticalSection(&my_winsec);
			CWinLock wlock(&my_winsec);
			CWinLock wlock2(&my_winsec);
			msgRecvQueue.push_back(i);
			// LeaveCriticalSection(&my_winsec);
#else
			chrono::milliseconds dure(100);
			// if (my_mutex.try_lock_for(dure)) {
			if(my_mutex.try_lock_until(chrono::steady_clock::now() + dure)){
				cout << "inMsgRecvQueue(),����һ��Ԫ�� ��" << i << endl;
				msgRecvQueue.push_back(i);
				my_mutex.unlock();
			}
			else {
				this_thread::sleep_for(0.1s);
				cout << "���ſ������ɱ����" << endl;
			}
			// unique_lock<recursive_mutex> sbguard1(my_mutex);
			// msgRecvQueue.push_back(i);
#endif
		}
		cout << "inMsgRecvQueue()����" << endl;
	}

	bool outMsgLULProc(int &command) {
		
		if (msgRecvQueue.empty()) {
			return false;
		}
		else {
#ifdef __WINDOWSJQ_
			EnterCriticalSection(&my_winsec);
			command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			LeaveCriticalSection(&my_winsec);
#else
			//unique_lock<timed_mutex> sbguard1(my_mutex);
			my_mutex.lock();
			this_thread::sleep_for(10s);
			//testfunc1();
			command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			my_mutex.unlock();
#endif
			return true;
		}
	}

	void outMsgRecvQueue() {
		int command = 0;
		for (int i = 0; i < 5000; i++) {
			bool result = outMsgLULProc(command);
			if (result == true) {
				cout << "outMsgRecvQueue(),ȡ��һ��Ԫ�� ��" << command << endl;
			}
			else {
				cout << "outMsgRecvQueue()ִ�е�δ��ȡ������" << endl;
			}
		}
		cout << "outMsgRecvQueue()����" << endl;
	}

	/*void testfunc1() {
		lock_guard<recursive_mutex> sbguard(my_mutex);
		testfunc2();
	}
	void testfunc2() {
		lock_guard<recursive_mutex> sbguard(my_mutex);
	}*/



	A() {
#ifdef  __WINDOWSJQ_
		InitializeCriticalSection(&my_winsec);
#endif
	}
private:
	list<int> msgRecvQueue;
	// mutex my_mutex;
	// recursive_mutex my_mutex;
	timed_mutex my_mutex;

#ifdef  __WINDOWSJQ_
	CRITICAL_SECTION my_winsec;// window�ٽ���
#endif

};

void class_12() {
	
	A myobja;
	thread myOutMsgObj(&A::outMsgRecvQueue, &myobja);
	thread myInMsgObj(&A::inMsgRecvQueue, &myobja);

	myInMsgObj.join();
	myOutMsgObj.join();
}