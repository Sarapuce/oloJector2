#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

constexpr auto not_set = -1;
constexpr auto x86     = 0;
constexpr auto x86_64  = 1;

using namespace std;

class DllManager
{
public:
	DllManager();
	DllManager(string path);

	void setPath(string path);
	void loadDll();

private:
	string	m_path;
	int		m_arch;
	int     m_length;
};

