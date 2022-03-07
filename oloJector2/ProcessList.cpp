#include "ProcessList.h"

ProcessList::ProcessList()
{
	m_nbOfProcess = 0;
	refreshList();
}

bool ProcessList::refreshList()
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	m_nbOfProcess = 0;
	
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		cout << "[-] CreateToolhelp32Snapshot failed";
		return false;
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32))
	{
		cout << "[-] Process32First failed";
		CloseHandle(hProcessSnap);
		return false;
	}

	do
	{
		Process p(pe32.th32ProcessID);
		m_processes[m_nbOfProcess] = p;
		m_nbOfProcess++;
	} while (Process32Next(hProcessSnap, &pe32) && m_nbOfProcess < 1024);

	CloseHandle(hProcessSnap);

	return true;
}

Process ProcessList::getProcess(int idProcess)
{
	if (idProcess < 1024)
	{
		return m_processes[idProcess];
	}
	else
	{
		cout << "[-] There is not more than 1024 processes";
		return Process();
	}
}

void ProcessList::printProcessList()
{
	cout << "Pid   | Process Name                                       | Arch" << endl;
	
	for (int i = 0; i < m_nbOfProcess; i++)
	{
		m_processes[i].printProcess();
	}
}