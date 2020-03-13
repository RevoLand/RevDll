#pragma once
#define DLLEXPORT __declspec(dllexport)
#include "ConfigController.h"
#include "memory.h"
#include "sql.h"

#define DEBUG

void initialize();
void console();

class Main
{
public:
	static sql* getConnection();
	static ConfigController* getConfig();
	static memory* getMemory();
};