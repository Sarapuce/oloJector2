#include <iostream>

using namespace std;

void printArgs(int argc, char** argv)
{
	cout << "[+] Number of arguments : " << argc << endl;
	for (int i = 0; i < argc; i++)
	{
		cout << "Argument " << i << " : " << argv[i] << endl;
	}
}

int main(int argc, char** argv)
{
	printArgs(argc, argv);

	return 0;
}