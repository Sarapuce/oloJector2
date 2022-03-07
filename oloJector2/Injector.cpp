#include "Injector.h"


Injector::Injector()
{
	m_dll = NULL;
	m_process = NULL;
}

Injector::Injector(DllManager* dll, Process* process)
{
	m_dll = dll;
	m_process = process;
}

bool Injector::inject()
{
	if (m_process->getArch() != m_dll->getArch())
	{
		cout << "[-] Arch mismatch" << endl;
		cout << "[-] Process arch : " << m_process->getArch() << endl;
		cout << "[-] Dll arch     : " << m_dll->getArch() << endl;
		return false;
	}

	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS,
		FALSE,
		m_process->getPid());

	HMODULE hkernel32 = GetModuleHandle(L"kernel32.dll");
	if (!hkernel32)
	{
		cout << "[-] Impossible to load kernel32";
		return false;
	}

	LPVOID loadLibrairyaddr = (LPVOID)GetProcAddress(hkernel32, "LoadLibraryA");
	LPVOID distantDllName = (LPVOID)VirtualAllocEx(processHandle, NULL, m_dll->getPath().length(), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!distantDllName)
	{
		cout  << "[-] Impossible de allocate memory in target";
		return false;
	}

	int nbBytes = WriteProcessMemory(processHandle,
		distantDllName,
		m_dll->getPath().c_str(),
		m_dll->getPath().length(),
		NULL);

	if (!nbBytes)
	{
		printf("Error WriteProcessMemory : %lu \n", GetLastError());
		cout << "[-] WriteProcessMemory failed";
		return false;
	}

	HANDLE threadID = CreateRemoteThread(
		processHandle,
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)loadLibrairyaddr,
		distantDllName,
		NULL,
		NULL);

	if (!threadID)
	{
		cout << "[-] Impossible to start a thread in the selected process";
		return false;
	}

	cout << "[+] Injected" << endl;

	CloseHandle(processHandle);
	CloseHandle(threadID);
	return true;
}