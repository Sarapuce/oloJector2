#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

#define NOT_SET -1
#define X86 0
#define X86_64 1

using namespace std;

class DllManager
{
public:
	DllManager();
	DllManager(string path);

	void setPath(string path);
	void loadDll();
	int getArch();

private:
	string	m_path;
	int		m_arch;
	int     m_length;
};

