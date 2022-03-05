#include "process.h"

Process::Process()
{
	m_pid			= 0;
	m_processName	= "<unknow>";
	m_arch			= NOT_SET;
}

Process::Process(int pid)
{
	m_pid = pid;
	getProcessInfo();
}

void Process::getProcessInfo()
{
	if (!m_pid)
	{
		cout << "[-] Pid of process not set" << endl;
		return;
	}

	// Get process name
	TCHAR name[MAX_PATH];

	HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, m_pid);
	GetProcessImageFileName(processHandle, name, MAX_PATH);
	
	// Convert TCHAR* to string
	wstring tempName = name;
	m_processName = CW2A(name);
	m_processName = m_processName.substr(m_processName.find_last_of("\\") + 1);

	cout << "[+] Get name of process " << m_pid << " : " << m_processName << endl;

	// Get arch of the process
	BOOL bIsWow64 = FALSE;

	typedef BOOL(WINAPI* LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fnIsWow64Process;

	// Handle to kernel32 to check which function is present in it
	HMODULE k32 = GetModuleHandle(TEXT("kernel32"));
	if (k32)
	{
		fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(k32, "IsWow64Process");

		// If fnIsWow64Process is not in kernel32 we are on a 32 bits OS
		if (NULL != fnIsWow64Process)
		{
			if (!fnIsWow64Process(processHandle, &bIsWow64))
			{
				cout << "[-] Error while checking arch of " << m_processName << endl;
			}
		}

		// bISWow64 true means we are running a 32 bits process on a 64 bits OS
		if (bIsWow64)
			m_arch = X86;
		else
			m_arch = X86_64;
	}

	CloseHandle(processHandle);

	cout << "[+] Get arch of process " << m_processName << " : " << m_arch << endl;
}

