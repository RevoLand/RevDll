#include "ConfigController.h"
#include <iostream>
#include "INIReader.h"
#include "Windows.h"

ConfigController::ConfigController()
{
	const INIReader reader(".\\Config\\config.ini");

	if (reader.ParseError() != 0) {
		std::cout << "Can't parse config file!!!\n";
	}

	// Level Limits
	level_cap = reader.GetInteger("level_cap", "ch_eu", 110);
	level_cap_pet = reader.GetInteger("level_cap", "pet", 110);

	mastery_cap_ch = reader.GetInteger("mastery_cap", "ch", 330);
	mastery_cap_eu = reader.GetInteger("mastery_cap", "eu", 220);

	// Disable & Fixes
	fix_rates = reader.GetBoolean("disable_fix", "fix_rates", true);
	disable_dumps = reader.GetBoolean("disable_fix", "disable_dumps", true);
	disable_green_book = reader.GetBoolean("disable_fix", "disable_green_book", true);
	disable_messages = reader.GetBoolean("disable_fix", "disable_messages", false);
	disable_logs = reader.GetBoolean("disable_fix", "disable_logs", false);

	// IP Spoofing
	ip_spoof = reader.GetBoolean("ip", "spoof", true);
	spoof_ip = reader.Get("ip", "ip", "127.0.0.1");

	// Job
	job_mgr_clamp_limit = reader.GetInteger("job", "manager_clamp_limit", 2134217728);

	// Gold Limits
	gold_limit_exchange = reader.GetInteger("gold_limits", "exchange", 1000000000);
	gold_limit_stall = reader.GetInteger("gold_limits", "stall", INT_MAX);

	// Capture the Flag
	ctf_reward_item = reader.Get("ctf", "reward_item", "ITEM_ETC_ARENA_COIN");
	ctf_reward_count = reader.GetInteger("ctf", "reward_item_count", 1);
	ctf_reward_param1 = reader.GetInteger("ctf", "reward_item_param1", 0);
	ctf_reward_param2 = reader.GetInteger("ctf", "reward_item_param2", 0);
	ctf_reward_param3 = reader.GetInteger("ctf", "reward_item_param3", 1);
	ctf_reward_param4 = reader.GetInteger("ctf", "reward_item_param4", 0);
	ctf_reward_param5 = reader.GetInteger("ctf", "reward_item_param5", 0);
	ctf_reward_param6 = reader.GetInteger("ctf", "reward_item_param6", 0);
	ctf_reward_param7 = reader.GetInteger("ctf", "reward_item_param7", 0);
	ctf_reward_param8 = reader.GetInteger("ctf", "reward_item_param8", 1);

	// Battle Arena
	battle_arena_reward_item = reader.Get("arena_rewards", "reward_item", "ITEM_ETC_ARENA_COIN");
	guild_arena_win_reward_item_count = reader.GetInteger("arena_rewards", "guild_win_reward_item_count", 7);
	guild_arena_lose_reward_item_count = reader.GetInteger("arena_rewards", "guild_lose_reward_item_count", 2);
	random_party_arena_win_reward_item_count = reader.GetInteger("arena_rewards", "party_win_reward_item_count", 7);
	random_party_arena_lose_reward_item_count = reader.GetInteger("arena_rewards", "party_lose_reward_item_count", 2);
	arena_reward_param1 = reader.GetInteger("arena_rewards", "reward_item_param1", 0);
	arena_reward_param2 = reader.GetInteger("arena_rewards", "reward_item_param2", 0);
	arena_reward_param3 = reader.GetInteger("arena_rewards", "reward_item_param3", 1);
	arena_reward_param4 = reader.GetInteger("arena_rewards", "reward_item_param4", 0);
	arena_reward_param5 = reader.GetInteger("arena_rewards", "reward_item_param5", 0);
	arena_reward_param6 = reader.GetInteger("arena_rewards", "reward_item_param6", 0);
	arena_reward_param7 = reader.GetInteger("arena_rewards", "reward_item_param7", 0);
	arena_reward_param8 = reader.GetInteger("arena_rewards", "reward_item_param8", 1);
}