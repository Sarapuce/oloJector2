#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <psapi.h>
#include <atlstr.h>

#define NOT_SET -1
#define X86 0
#define X86_64 1

using namespace std;

class Process
{
public:
	Process();
	Process(int pid);

	void getProcessInfo();
	void printProcess();
	int getArch();
	int getPid();

private:
	int m_pid;
	string m_processName;
	int m_arch;
};

