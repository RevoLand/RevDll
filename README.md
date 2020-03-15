Here is a sum of current features and things to-do.
---
### Level Settings `[level_cap]`
- [x] CH ~ EU Level Cap `ch_eu=110`
- [x] Pet Level Cap `pet=110`
---
### Mastery Cap Settings `[mastery_cap]`
- [x] CH Mastery Cap `ch=330`
- [ ] EU Mastery Cap `eu=220`
---
### Disable & Fix `[disable_fix]`
- [x] Fix Rate Limits (2.5x) `fix_rates=1`
- [x] Disable .DMP Generation `disable_dumps=1`
- [x] Disable Green Book `disable_green_book=1`
- [x] Disable GS Window Messages `disable_messages=0`
- [x] Disable LOG DATABASE INTERACTIONS `disable_logs=0`
- [x] Disable (%s register gold price) error popup `npc_register_gold_price_error=1`
- [x] Disable (%s register silk price) error popup `npc_register_silk_price_error=1`
---
### IP Spoof for Cert `[ip]`
- [x] Enable Spoofing `spoof=1`
- [x] Spoof IP `ip=127.0.0.1`
---
### Gold Limits `[gold_limits]`
*Those settings are limited by **int32**.maxValue, Stall limit is set to 500B statically.*
- [x] Exchange Gold Limit `exchange=1000000000`
- [x] Stall Gold Limit `stall=5000000000` *(TODO: Investigate the math behind.)*
---
### Party Settings `[party]`
- [x] Party Monster Spawn minimum required player count `monster_spawn_min_member_count=2`
- [x] Party Monster Spawn Chance, as % `monster_spawn_chance=100` **(Doesn't seems to be affecting champion/giant mobs.)*

---
### Academy Settings `[academy]`
- [x] Create Penalty *(in seconds)* `create_penalty_seconds=604800`
- [x] Disband Penalty *(in seconds)* `disband_penalty_seconds=604800`
- [x] Graduate Level `graduate_level=40`
---
### Guild Settings `[guild]`
- [x] Union Chat permission limit `union_chat_limit=12` **(Requires client edit too)*
- [ ] Leaving Penalty *(in seconds)* `leaving_penalty=60`
---
### Unique `[unique]`
- [x] Summon Skill Spawn Limit `summon_skill_spawn_limit=50`
---
### Capture the Flag `[ctf]`
- [x] Reward Item `reward_item=ITEM_ETC_ARENA_COIN`
- [x] Reward Item Count `reward_item_count=1`
- [x] Reward Item Parameters (1-8) `reward_item_param1=0`
---
### Battle Arena `[battle_arena]`
- [x] Guild Arena Win Reward Item Count `guild_win_reward_item_count=7`
- [x] Guild Arena Lose Reward Item Count `guild_lose_reward_item_count=2`
- [x] Random Party Arena Win Reward Item Count `party_win_reward_item_count=5`
- [x] Random Party Arena Lose Reward Item Count `party_lose_reward_item_count=1`
- [x] Reward Item `reward_item=ITEM_ETC_ARENA_COIN`
- [x] Reward Item Parameters (1-8) `reward_item_param1=0`
---
### Job `[job]`
- [x] Level Cap `level_cap=7`
- [ ] Leaving Penalty *(in seconds)* `leaving_penalty=60`
- [x] Job Manager Clamp Limit `manager_clamp_limit=2134217728`
