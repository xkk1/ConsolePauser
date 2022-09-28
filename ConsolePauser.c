#include <Windows.h>
#include <Psapi.h>
#include <stdio.h>
#include <conio.h>
int main(int argc, char *argv[])
{
    if (argc < 2) {
    	printf("�÷���\n%s <�ļ���> <����>\n�밴���������. . .", argv[0]);
    	getch();
    	return -1;
	}
    CHAR Command[MAX_PATH];
    STARTUPINFO StartupInfo;
    PROCESS_INFORMATION ProcessInfo;
    PROCESS_MEMORY_COUNTERS ProcessMemoryCounters;
    LARGE_INTEGER StartingTime, EndingTime, Frequency;
    DWORD ReturnValue;
    strcpy(Command, argv[1]);
    int i;
    for (i = 2; i < argc; i++) {
    	strcat(Command, " ");
		strcat(Command, argv[i]);
	}
    SetConsoleTitle(Command);
    memset(&ProcessInfo, 0, sizeof(ProcessInfo));
    memset(&StartupInfo, 0, sizeof(StartupInfo));
    StartupInfo.cb = sizeof(StartupInfo);
    if (!CreateProcess(NULL, Command, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo)) {
    	printf("\n�޷��������̣�%s\n�밴���������. . .", Command);
		getch();
		return -1;
	}
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&StartingTime);
    WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
    QueryPerformanceCounter(&EndingTime);
    GetProcessMemoryInfo(ProcessInfo.hProcess, &ProcessMemoryCounters, sizeof(ProcessMemoryCounters));
    GetExitCodeProcess(ProcessInfo.hProcess, &ReturnValue);
    LONGLONG ExecutionTime = (EndingTime.QuadPart - StartingTime.QuadPart) * 1000000 / Frequency.QuadPart;
    printf("\n-----------------------------------------------");
    printf("\nִ��ʱ�䣺%lld.%lld ms", ExecutionTime / 1000, ExecutionTime % 1000);
    printf("\n����ڴ�ʹ�ã�%u KB", (unsigned)(ProcessMemoryCounters.PeakWorkingSetSize >> 10));
    printf("\n���򷵻�ֵ��%u (0x%X)", ReturnValue, ReturnValue);
    printf("\n-----------------------------------------------");
    printf("\n�밴���������. . .");
    getch();
    return 0;
}
