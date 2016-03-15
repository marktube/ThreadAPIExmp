// ThreadAPIExmp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int g_Num_One = 0;
CRITICAL_SECTION g_cs;

DWORD WINAPI ThreadProc(LPVOID lpParam){
	int nTmp = 0;
	for (int i = 0; i < 10; i++){
		//进入临界区
		EnterCriticalSection(&g_cs);
		nTmp = g_Num_One;
		nTmp++;
		Sleep(1);
		g_Num_One = nTmp;
		//离开临界区
		LeaveCriticalSection(&g_cs);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	InitializeCriticalSection(&g_cs);

	HANDLE hThread[10] = {0};
	for (int i = 0; i < 10; i++){
		hThread[i]=CreateThread(NULL,//指明创建进程的安全属性，一般为NULL
			0,//initial stack size 初始堆栈大小
			ThreadProc,//thread function 指定线程函数
			NULL,//thread argument 参数传递，可以是任意类型的指针
			0,//creation option 创建线程后的线程状态 0表示立即执行
			NULL);//thread identifier 线程id
	}
	//等待线程执行后再执行，以免主线程执行完后退出
	//WaitForSingleObject(hThread, INFINITE);
	WaitForMultipleObjects(10, hThread, TRUE, INFINITE);
	printf("main:%d\r\n",g_Num_One);
	for (int i = 0; i < 10; i++)
		CloseHandle(hThread[i]);
	DeleteCriticalSection(&g_cs);
	return 0;
}

