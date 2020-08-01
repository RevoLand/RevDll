#pragma once
#include "DllMain.h"

#define GOBJ_GET_CHAR_NAME_FUNC_OFFSET                                0x004A66D0
#define GOBJ_GET_NICK_NAME_FUNC_OFFSET                                0x004DDC50

class FixController
{
public:
	static void initialize();
	static void party();
private:
	//static void update_siege_introduction(char* introduction_text, int fortress_id, int guild_id);
	static void update_siege_introduction();
	static void level_cap();
	static void mastery_cap();
	static void disable_fix();
	static int on_dump_function(const char* a);
	static void ip();
	static void gold_limits();
	static void academy();
	static void guild();
	static void unique();
	static void ctf();
	static void arena_rewards();
	static void job();
};