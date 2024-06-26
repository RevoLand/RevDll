#pragma once
#define CALL(a) _asm call [a]
#define JMP(a) _asm jmp [a]
#include <windows.h>

typedef unsigned char byte;

template<typename T>
int addr_from_this(T funptr) {
	union {
		int addr;
		T ptr;
	} myu;

	myu.ptr = funptr;
	return myu.addr;
}

template<typename T>
void placeHook(int trampoline_location, T& target_location)
{
	placeHook(trampoline_location, reinterpret_cast<int>(&target_location));
}

void placeHook(int trampoline_location, int target_location);
void replaceOffset(int trampoline_location, int target_location);
void replaceAddr(int addr, int value);
void vftableHook(unsigned int vftable_addr, int offset, int target_func);

void RenderJMPInstruction(LPVOID address, LPVOID jumpto, char* buf);
void JMPFunction(DWORD address, DWORD jumpto);
void RenderCALLInstruction(LPVOID address, LPVOID jumpto, char* buf);
void CALLFunction(DWORD address, DWORD jumpto);