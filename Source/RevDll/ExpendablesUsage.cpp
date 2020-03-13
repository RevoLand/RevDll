#include "ExpendablesUsage.h"
#include "hook.h"
#include "CGObj.h"

void ExpendablesUsage::Initialize(void)
{
	replaceOffset(0x0049C336, addr_from_this(&CGObj::GetTID));
}