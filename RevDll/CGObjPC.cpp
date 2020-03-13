#include "CGObjPC.h"

CGObjPC* CGObjPC::GetObjPCByCharName(const char* charname)
{
	return reinterpret_cast<CGObjPC*(__cdecl*)(const char*)>(0x00485E20)(charname);
}

void CGObjPC::UpdateGold(long long amount, int updatetype, int a3, int notify)
{
	reinterpret_cast<void(__thiscall*)(CGObjPC*, long long, int, int, int)>(this->vftable->UpdateGoldFunPtr)(this, amount, updatetype, a3, notify);
}