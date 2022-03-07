#pragma once
#include <Windows.h>
#include <tlhelp32.h>

#include "Process.h"


class ProcessList
{
public:
	ProcessList();

	bool refreshList();
	Process getProcess(int idProcess);
	void printProcessList();

private:
	int m_nbOfProcess;
	Process m_processes[1024];

};

