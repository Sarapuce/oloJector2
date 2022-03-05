#include <iostream>
#include "dllManager.h"

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

	dllManager* dll = new dllManager(argv[1]);
	return 0;
}