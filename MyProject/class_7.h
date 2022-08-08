#pragma once
#pragma once
#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
// ���ģʽ����Ŀ����ģʽ �ܽ�õ���
// �������ģʽ �� ������Ŀ����ĳ������ĳЩ������� ֻ�ܴ���һ������
// call_once()	�����ܹ���֤����a����ֻ������һ�� �߱�����������  ��Ҫ��һ����ǽ��ʹ�� once_flag
std::mutex resource_mutex;
std::once_flag g_flag;

class MyCAS {
private:
	MyCAS() {}; //˽�л����캯��

private:
	static MyCAS* m_instance;

public:
	static void CreateInstance() {
		chrono::milliseconds dura(5000);
		this_thread::sleep_for(dura);
		cout << "CreateInstance��ִ����" << endl;
		m_instance = new MyCAS();
		static CGarhuishou c1;
	}

	static MyCAS* GetInstance() {
		// ���Ч��
		if (m_instance == NULL) { //˫������
			unique_lock<mutex> mymutex(resource_mutex); //������Ϊ�˷�ֹ���߳��ظ���ʼ��
			if (m_instance == NULL) {
				CreateInstance();
			}
		}

		/*std::call_once(g_flag, CreateInstance);
		cout << "call_onceִ������" << endl;*/
		return m_instance;
	}
	class CGarhuishou {
	public:
		~CGarhuishou() {
			if (MyCAS::m_instance) {
				delete MyCAS::m_instance;
				MyCAS::m_instance = NULL;
			}
		}
	};
	void func() {
		cout << "test" << endl;
	}
};

MyCAS* MyCAS::m_instance = NULL;// ��̬������������ �����ʼ��

void mythread() {
	cout << "�ҵ��߳̿�ʼ��" << endl;
	MyCAS* p_a = MyCAS::GetInstance();
	cout << "�ҵ��߳̽�����" << endl;
}

void class_7() {
	//MyCAS* m_instance = MyCAS::GetInstance();
	// ��������GetInstance����
	//m_instance->func();
	//MyCAS::GetInstance()->func();
	//cout << MyCAS::GetInstance << " " << &MyCAS::GetInstance << endl;

	thread myobj1(mythread);
	thread myobj2(mythread);

	myobj1.join();
	myobj2.join();
}