#include "CGObj.h"
#include "ObjectData.h"
#include "CGObjPC.h"

const unsigned int dwCall = 0x00485C90;

void GoldObtainScroll(CGObjPC* pc, CInstanceObj* item)
{
	if (pc && item && item->objitem->Param1 == 666)
	{
		long long goldamount = 0;
		goldamount = _atoi64(item->objitem->Desc1.c_str());
		if (goldamount)
			pc->UpdateGold(goldamount, 25, 1, 1);
	}
}

unsigned short* CGObj::GetTID(void)
{
	unsigned short* res = nullptr;

	__asm
	{
		call dwCall;
		mov res, eax;
	}

	if (res && *res == 0xC6ED)
	{
		__asm
		{
			mov dword ptr ds : [ebp + 4], 0x0049C734;
			mov eax, [ebp + 0x18];
			mov word ptr ds : [eax], 1; //ErrorCode
			mov eax, [esi + 0x34];
			
			push eax;
			push ebx;
			call GoldObtainScroll;
			add esp, 8;
		}
		
	}
	return res;
}