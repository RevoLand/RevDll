#include "DllMain.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <windows.h>

#include "FixController.h"
#include "sql.h"
#include "UniqueController.h"

sql* sql_connection = new sql();
ConfigController* configs = new ConfigController();
memory* memory_helper = new memory();

DLLEXPORT BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason != DLL_PROCESS_ATTACH)
	{
		return true;
	}

	// Debug Console
	AllocConsole();

	// Make console writeable
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	std::cout << "[RevDll] Initializing - v0.1\n";

	// Start sql connection & create console thread
	CreateThread(nullptr, NULL, LPTHREAD_START_ROUTINE(initialize), nullptr, NULL, nullptr);

	// Init fixes
	FixController::initialize();

	// Init unique controller
	UniqueController::initialize();
	return true;
}

void initialize()
{
	sql_connection->connect();

	// doesn't works.
	//CloseWindow(::FindWindowW(nullptr, L"SQLAPI++ Registration Reminder"));

	console();
}

void console()
{
	std::cout << "[RevDll] Type your command.\n";
	std::string input;
	std::cin >> input;

	if (input == "exit")
	{
		std::cout << "[RevDll] COMMAND FOUND!\n";
	}

	console();
}

sql* Main::getConnection()
{
	return sql_connection;
}

ConfigController* Main::getConfig()
{
	return configs;
}

memory* Main::getMemory()
{
	return memory_helper;
}