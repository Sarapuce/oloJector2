#include <iostream>
#include "dllManager.h"
#include "Process.h"

using namespace std;

void printArgs(int argc, char** argv)
{
	cout << "[+] Number of arguments : " << argc << endl;
	for (int i = 0; i < argc; i++)
	{
		cout << "[+] Argument " << i << " : " << argv[i] << endl;
	}
}

int main(int argc, char** argv)
{
	printArgs(argc, argv);

	if (argc < 2)
	{
		cout << "[-] Not enough arguments" << endl << "[-] Usage : " << argv[0] << " dllname.dll";
		return 1;
	}

	DllManager* dll = new DllManager(argv[1]);
	Process* p_32 = new Process(19152);
	Process* p_64 = new Process(19236);
	Process* p_null = new Process();
	return 0;
}