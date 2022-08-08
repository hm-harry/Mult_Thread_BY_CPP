#pragma once
// thread t1(函数地址，实例化对象地址（&，ref）， 参数)		t1.join()	t1.detach
// this_thread::get_id()
//my_mutex.lock()		my_mutex.unlock()		lock_guard<mutex> l(my_mutex, adopt)		不常见lock(mutex 1, mutex 2)	
// unique_lock<mutex> sbguard1(my_mutex1);
//std::chrono::milliseconds dura(20); //20ms   std::this_thread::sleep_for(dura);    unique_lock<mutex> sbguard1(my_mutex1, adopt_lock);
// 必须提前加锁:adopt_lock		肯定不能提前加锁: try_to_lock尝试加锁owns_lock		defer_lock不用unlock try_lock
//once_flag a          call_once(a, 函数名)      
// condition_variable a        a.wait()               a.notify_one
// future<T> result = async(mythread); result.get();  result.wait();
// packaged_task<函数返回值类型(函数输入类型)>变量名(函数名);      thread t1(ref(变量名), 函数输入);    future<返回值类型> result = 变量名.get_future();
// promise可以保存一个值   promise<T> pro;   pro.set_value(T)     future<T> f = pro.get_future()    f.get();
// future_status  .wait_for  timeout  ready  deferred				shared_future 不仅仅是移动了  而是复制					原子操作atomic 
// recursive_mutex       timed_mutex(try_lock_for(),try_lock_until)       recursive_timed_mutex