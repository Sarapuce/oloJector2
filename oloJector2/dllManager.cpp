#include "DllManager.h"

// Initialize an empty dllManager
DllManager::DllManager()
{
	m_path   = "";
	m_arch   = NOT_SET;
	m_length = 0;
}

// Initialize a dllManager. We load the dll to have all needed information
DllManager::DllManager(string path)
{
	m_path = path;
	loadDll();
}

void DllManager::setPath(string path)
{
	m_path = path;
}

void DllManager::loadDll()
{
	cout << "[+] Loading dll : " << m_path << endl;

	ifstream dll_file(m_path, ios::binary);
	
	// Can we open the file ? If not, it doesn't exist
	if (!dll_file)
	{
		cout << "[-] Dll not found" << endl;
		m_arch   = NOT_SET;
		m_length = 0;
		return;
	}

	// Constant to find arch
	char buffer[512];
	const char pattern_x86_64[] = { 0x02, 0x02, 0x64, 0x86, 0x00 };
	const char pattern_x86[]    = { 0x02, 0x02, 0x4c, 0x01, 0x00 };

	// Read the file
	if (!(dll_file.read(buffer, sizeof(buffer))))
	{
		cout << "[-] Impossible to read the dll";
		return;
	}

	// Get file size
	dll_file.seekg(0, std::ios::end);
	m_length = (size_t)dll_file.tellg();
	dll_file.seekg(0, std::ios::beg);

	// Set all 0 bytes to 2 to avoid end of string 
	// TODO : Change the arch detection
	for (unsigned int i = 0; i < 511; i++)
	{
		if (buffer[i] == 0)
		{
			buffer[i] = 2;
		}
	}
	buffer[511] = 0;

	dll_file.close();

	// Compare information get in the buffer to determine the arch
	if (strstr(buffer, pattern_x86))
	{
		cout << "[+] Dll " << m_path << " loaded" << endl;
		cout << "[+] Detected arch : x86" << endl;
		m_arch = X86;
		return;
	}

	if (strstr(buffer, pattern_x86_64))
	{
		cout << "[+] Dll " << m_path << " loaded." << endl;
		cout << "[+] Detected arch : x86_64" << endl;
		m_arch = X86_64;
		return;
	}

	cout << "[-] Dll arch not recognized" << endl;
}

int DllManager::getArch()
{
	return m_arch;
}

int DllManager::getLength()
{
	return m_length;
}