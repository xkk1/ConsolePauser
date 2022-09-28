#include <Windows.h>
#include <Psapi.h>
#include <stdio.h>
#include <conio.h>
int main(int argc, char *argv[])
{
    if (argc < 2) {
    	printf("用法：\n%s <文件名> <参数>\n请按任意键继续. . .", argv[0]);
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
    	printf("\n无法创建进程：%s\n请按任意键继续. . .", Command);
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
    printf("\n执行时间：%lld.%lld ms", ExecutionTime / 1000, ExecutionTime % 1000);
    printf("\n最大内存使用：%u KB", (unsigned)(ProcessMemoryCounters.PeakWorkingSetSize >> 10));
    printf("\n程序返回值：%u (0x%X)", ReturnValue, ReturnValue);
    printf("\n-----------------------------------------------");
    printf("\n请按任意键继续. . .");
    getch();
    return 0;
}
