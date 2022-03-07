#pragma once

#include "Process.h"
#include "DllManager.h"


class Injector
{
public:
	Injector();
	Injector(DllManager* dll, Process* process);

	bool inject();

private:
	DllManager* m_dll;
	Process* m_process;

};

