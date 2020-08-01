#include "ChatController.h"
#include "DllMain.h"
#include <iostream>
#include <string>
#include "hook.h"
#include <cstdio>

#include "memhelp.h"
#include "xlib.h"

const DWORD dwNormalChatHookAddr = 0x004B18FE;
const DWORD dwNormalChatHookJumpback = 0x004B1905;
const DWORD dwPartyChatHookJumpback = 0x004077d0;

std::string* chat;
std::string* charname;

void HandleNormalChat()
{
	if (chat->length() && charname->length())
	{
		printf("%s is saying (%s).\n", charname->c_str(), chat->c_str());
	}
}

void __declspec(naked) OnChatHook(void)
{
	__asm mov edi, [esp + 0x38];
	__asm add esp, 0x4;

	__asm push eax;
	__asm lea eax, [esp + 0x38];
	__asm mov chat, eax;
	__asm lea eax, [esp + 0x54];
	__asm mov charname, eax;
	__asm pop eax;

	__asm pushad;
	HandleNormalChat();
	__asm popad;

	__asm jmp dwNormalChatHookJumpback;
}

int ecxx;
int eaxx;
int test;
const DWORD levelup_jmpback = 0x0059c613;
void __declspec(naked) OnEUMastery()
{
	__asm mov ecxx, ecx; // new mastery level
	__asm push ecx;
	__asm mov eaxx, eax; // player current level
	__asm push eax;
	__asm mov test, edx;

	__asm pushad;
	printf("ecx: [%i] eax: [%i] test: [%i]", ecxx, eaxx, test);
	__asm popad;

	__asm cmp ecx, eax
	__asm jmp levelup_jmpback;
}

void ChatController::initialize()
{
	std::cout << "======================== [Chat Controller] ========================" << std::endl;
	memhelp::RenderNop((void*)dwNormalChatHookAddr, 7);
	memhelp::RenderDetour(ASM_JMP, (void*)dwNormalChatHookAddr, OnChatHook);

	//memhelp::RenderNop((void*)0x0059c611, 2);
	//memhelp::RenderDetour(ASM_JMP, (void*)0x0059c611, OnEUMastery);

	std::cout << "======================== [Chat Controller] ========================" << std::endl;
}

/*
	SACommand cmd;
	try
	{
		cmd.setConnection(&main::getConnection()->connection);
		cmd.setCommandText("_LogUniqueKill");
		cmd.Param("UniqueCodeName").setAsString() = unique_codename;
		cmd.Param("KillerCharacterName").setAsString() = character_name;
		cmd.Execute();
#ifdef DEBUG
		std::cout << "[SQL-DEBUG] -> [_LogUniqueKill] procedure executed" << std::endl;
#endif
	}
	catch (SAException & e)
	{
#ifdef DEBUG
		printf("[SQL-DEBUG] -> failed to execute procedure  [_LogUniqueKill]\nException:[%s]\n", static_cast<const char*>(e.ErrText()));
#endif
	}
 */