#include "hook.h"

#include <SDKDDKVer.h>
#include <windows.h>
#include <iostream>

typedef unsigned char byte;

void placeHook(int trampoline_location, int target_location)
{
	char jmp_inst[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
	int distance;
	DWORD dwProtect = 0;

	distance = target_location - trampoline_location - 5;

	// Write jump-distance to instruction
	memcpy((jmp_inst + 1), &distance, 4);

	if (!VirtualProtect((LPVOID)trampoline_location, sizeof(jmp_inst), PAGE_EXECUTE_READWRITE, &dwProtect)) {
		perror("Failed to unprotect memory\n");
		return;
	}

	memcpy((LPVOID)trampoline_location, jmp_inst, sizeof(jmp_inst));

	VirtualProtect((LPVOID)trampoline_location, sizeof(jmp_inst), dwProtect, nullptr);
}

void replaceOffset(int trampoline_location, int target_location)
{
	char inst_offset[] = { 0x00, 0x00, 0x00, 0x00 };
	int distance;
	DWORD dwProtect = 0;

	int offset_location = trampoline_location + 1;

	distance = target_location - trampoline_location - 5;

	// Write jump-distance to instruction
	memcpy(inst_offset, &distance, 4);

	if (!VirtualProtect((LPVOID)offset_location, sizeof(inst_offset), PAGE_EXECUTE_READWRITE, &dwProtect)) {
		perror("Failed to unprotect memory\n");
		return;
	}

	memcpy((LPVOID)offset_location, inst_offset, sizeof(inst_offset));

	VirtualProtect((LPVOID)offset_location, sizeof(inst_offset), dwProtect, nullptr);
}

void replaceAddr(int addr, int value)
{
	DWORD dwProtect;

	if (!VirtualProtect((LPVOID)addr, sizeof(int), PAGE_EXECUTE_READWRITE, &dwProtect)) {
		perror("Failed to unprotect memory\n");
		return;
	}

	*((int*)addr) = value;

	VirtualProtect((LPVOID)addr, sizeof(int), dwProtect, nullptr);
}

void vftableHook(unsigned int vftable_addr, int offset, int target_func)
{
	replaceAddr(vftable_addr + offset * sizeof(void*), target_func);
}
void CALLFunction(DWORD address, DWORD jumpto)
{
	try
	{
		int res = 0;
		char instruction[5];
		RenderCALLInstruction((LPVOID)address, (LPVOID)jumpto, instruction);
		DWORD oldprot, dummy;

		res = VirtualProtect((void*)address, 5, PAGE_EXECUTE_READWRITE, &oldprot);

		if (res == 0)
		{
			throw - 1;
		}
		memcpy((LPVOID)address, (LPVOID)instruction, 5);

		res = VirtualProtect((void*)address, 5, oldprot, &dummy);
		if (res == 0)
		{
			throw - 2;
		}
	}
	catch (int ex) { printf(":CALLFUNCTION failed with ex [%d]", ex); }
}

void RenderCALLInstruction(LPVOID address, LPVOID jumpto, char* buf)
{
	try
	{
		int offset = (int)jumpto - ((int)address + 5);
		buf[0] = (char)0xE8;
		*(DWORD*)(buf + 1) = offset;
	}
	catch (int ex) { printf(":RenderCallInstruction failed with ex [%d]", ex); }
}

void JMPFunction(DWORD address, DWORD jumpto)
{
	try
	{
		bool res = false;
		char instruction[5];
		RenderJMPInstruction((LPVOID)address, (LPVOID)jumpto, instruction);
		DWORD oldprot, dummy;
		res = VirtualProtect(reinterpret_cast<void*>(address), 5, PAGE_EXECUTE_READWRITE, &oldprot);
		if (res == false)
		{
			throw - 1;
		}
		memcpy(reinterpret_cast<LPVOID>(address), static_cast<LPVOID>(instruction), 5);

		res = VirtualProtect(reinterpret_cast<void*>(address), 5, oldprot, &dummy);
		if (res == false)
		{
			throw - 2;
		}
	}
	catch (int ex) { printf(":JMPFunction failed with ex [%d]", ex); }
}

void RenderJMPInstruction(LPVOID address, LPVOID jumpto, char* buf)
{
	try
	{
		int offset = (int)jumpto - ((int)address + 5);
		buf[0] = (char)0xE9;
		*(DWORD*)(buf + 1) = offset;
	}
	catch (int ex) { printf(":RenderJMPInstruction failed with ex [%d]", ex); }
}