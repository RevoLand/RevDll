#pragma once
class FixController
{
public:
	static void initialize();
	static void party();
private:
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