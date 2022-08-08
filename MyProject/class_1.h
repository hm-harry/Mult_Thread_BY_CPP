#pragma once
#include<iostream>
#include<thread>
using namespace std;

void class_1() {
	// 并发、进程、线程
	// 并行 两个或者更多的任务同时进行      并发 交替运行
	// 进程 一个可执行程序运行起来就是一个进程
	// 线程 每个进程都有一个主线程 一个进程只能有一个主线程 与进程唇齿相依
	// 除了主线程之外我们可以通过自己写代码创建其他线程 其他线程走的别的道路 甚至去不同地方（多线程）
	// 每个线程需要一个独立的堆栈空间（1m）
	// 进程之间的通信（同一台电脑上：管道，文件，消息队列，共享内存） （不同电脑：socket）
	// 多线程并发 数据一致性问题

	// 以往：创建线程： windows:CreateThread(), _beginthread(), _beginthreadexe()   linux:pthread_create()  库：POSIX thraed(pthread)
	// c++11：本身增加了多线程的支持，可移植性
	// 临界区，互斥量

	cout << "hello world" << endl;
}