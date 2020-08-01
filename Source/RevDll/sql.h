#pragma once
#include "include/SQLAPI.h"

class sql
{
public:
	void connect();
	void execute(char* query);
	SAConnection connection;
};