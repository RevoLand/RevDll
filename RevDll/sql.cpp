#include "sql.h"

#include <cstdio>
#include <iostream>

#include "IniReader.h"

void sql::connect()
{
	printf("[RevDll] Initializing SQL Connection...\n");

	const INIReader reader(".\\Config\\sql.ini");

	if (reader.ParseError() != 0) {
		std::cout << "[RevDll] Can't parse config file!!!\n";
	}

	const auto host = reader.Get("sql", "sqlHostDB", "");
	const auto user = reader.Get("sql", "sqlUser", "");
	const auto pass = reader.Get("sql", "sqlPass", "");
	printf("[RevDll] SQL Settings read.\n");
	try
	{
		connection.Connect(host.c_str(), user.c_str(), pass.c_str(), SA_SQLServer_Client);
		printf("[RevDll] Database Connection Established.\n");
	}
	catch (SAException & a)
	{
		printf("[RevDll] !!! Could not connect to DB!!!\n");
#ifdef DEBUG
		printf("sql::connect() -> EXCEPTION %s", static_cast<const char*>(a.ErrText()));
#endif
	}
}

void sql::execute(char* query)
{
	SACommand cmd;
	try
	{
		cmd.setConnection(&this->connection);
		cmd.setCommandText(query);
		cmd.Execute();

		this->connection.Commit();
#ifdef DEBUG
		printf("DEBUG -> query executed [%s]\n", query);
#endif
	}
	catch (SAException & e)
	{
#ifdef DEBUG
		printf("DEBUG -> failed to execute query [%s]\nException:[%s]\n", query, (const char*)e.ErrText());
#endif
	}
}