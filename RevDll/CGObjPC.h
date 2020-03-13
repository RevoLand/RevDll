#pragma once

class CGObjPCVftable
{
public:
	char pad_0000[0x16C]; //0x0000
	int UpdateGoldFunPtr; //0x016C
};

class CGObjPC
{
public:
	CGObjPCVftable* vftable;

	static CGObjPC* GetObjPCByCharName(const char* charname);
	void UpdateGold(long long amount, int updatetype, int a3, int notify);
};