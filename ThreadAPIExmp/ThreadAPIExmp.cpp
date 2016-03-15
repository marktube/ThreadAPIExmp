// ThreadAPIExmp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

int g_Num_One = 0;
CRITICAL_SECTION g_cs;

DWORD WINAPI ThreadProc(LPVOID lpParam){
	int nTmp = 0;
	for (int i = 0; i < 10; i++){
		//�����ٽ���
		EnterCriticalSection(&g_cs);
		nTmp = g_Num_One;
		nTmp++;
		Sleep(1);
		g_Num_One = nTmp;
		//�뿪�ٽ���
		LeaveCriticalSection(&g_cs);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	InitializeCriticalSection(&g_cs);

	HANDLE hThread[10] = {0};
	for (int i = 0; i < 10; i++){
		hThread[i]=CreateThread(NULL,//ָ���������̵İ�ȫ���ԣ�һ��ΪNULL
			0,//initial stack size ��ʼ��ջ��С
			ThreadProc,//thread function ָ���̺߳���
			NULL,//thread argument �������ݣ��������������͵�ָ��
			0,//creation option �����̺߳���߳�״̬ 0��ʾ����ִ��
			NULL);//thread identifier �߳�id
	}
	//�ȴ��߳�ִ�к���ִ�У��������߳�ִ������˳�
	//WaitForSingleObject(hThread, INFINITE);
	WaitForMultipleObjects(10, hThread, TRUE, INFINITE);
	printf("main:%d\r\n",g_Num_One);
	for (int i = 0; i < 10; i++)
		CloseHandle(hThread[i]);
	DeleteCriticalSection(&g_cs);
	return 0;
}

