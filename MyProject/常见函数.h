#pragma once
// thread t1(������ַ��ʵ���������ַ��&��ref���� ����)		t1.join()	t1.detach
// this_thread::get_id()
//my_mutex.lock()		my_mutex.unlock()		lock_guard<mutex> l(my_mutex, adopt)		������lock(mutex 1, mutex 2)	
// unique_lock<mutex> sbguard1(my_mutex1);
//std::chrono::milliseconds dura(20); //20ms   std::this_thread::sleep_for(dura);    unique_lock<mutex> sbguard1(my_mutex1, adopt_lock);
// ������ǰ����:adopt_lock		�϶�������ǰ����: try_to_lock���Լ���owns_lock		defer_lock����unlock try_lock
//once_flag a          call_once(a, ������)      
// condition_variable a        a.wait()               a.notify_one
// future<T> result = async(mythread); result.get();  result.wait();
// packaged_task<��������ֵ����(������������)>������(������);      thread t1(ref(������), ��������);    future<����ֵ����> result = ������.get_future();
// promise���Ա���һ��ֵ   promise<T> pro;   pro.set_value(T)     future<T> f = pro.get_future()    f.get();
// future_status  .wait_for  timeout  ready  deferred				shared_future ���������ƶ���  ���Ǹ���					ԭ�Ӳ���atomic 
// recursive_mutex       timed_mutex(try_lock_for(),try_lock_until)       recursive_timed_mutex