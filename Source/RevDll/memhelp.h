#pragma once
#include <Windows.h>
#include "xlib.h"

class memhelp
{
public:

	//Templates
	template<typename T>
	inline static T& RefPtr(uintptr_t ptr)
	{
		return *reinterpret_cast<T*>(ptr);
	}

	//Bigger funcs go to cpp file
	static bool RenderDetour(uint8_t instruction, void* source, void* dest);
	static bool RenderNop(void* addr, uint32_t count);

	static bool WriteMem(void* addr, void* data, uint32_t count);
	static uint8_t* ReadMem(void* addr, uint32_t count);
private:
};