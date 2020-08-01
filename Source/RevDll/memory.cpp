#include "memory.h"
#include <Windows.h>

memory::memory() {
	try
	{
		this->cur_process = GetCurrentProcess();
	}
	catch (...)
	{
		printf("memory::memory constructor -> GetCurrentProcess failed\n");
		this->cur_process = (HANDLE)-1;
	}
}

memory::~memory() {
}

//write decimal number
void memory::WriteNumber(DWORD d_offset, DWORD d_val)
{
	WriteProcessMemory(this->cur_process, (LPVOID)d_offset, &d_val, sizeof(d_val), nullptr);
}

// write single byte
void memory::WriteByte(DWORD d_offset, DWORD d_byte)
{
	WriteProcessMemory(this->cur_process, (LPVOID)d_offset, &d_byte, 1, nullptr);
}

// Write chars array to memory
void memory::WriteString(DWORD d_offset, char* s_val)
{
	long nLen = strlen(s_val);
	for (long i = 0; i < nLen; i++)
	{
		char chr = INT(s_val[i]);
		DWORD n_offset = d_offset + i;
		WriteProcessMemory(this->cur_process, (LPVOID)n_offset, &chr, 1, nullptr);
	}
}

// Write double to memory
void memory::WriteDouble(DWORD d_offset, double s_val)
{
	try
	{
		/*
		auto ptr = reinterpret_cast<const unsigned char*>(&s_val);
		for (size_t i = 0; i < sizeof(s_val); ++i)
		{
			DWORD n_offset = d_offset + i;
			WriteProcessMemory(this->cur_process, LPVOID(n_offset), &ptr[i], 1, nullptr);
		}
		*/

		WriteProcessMemory(this->cur_process, (LPVOID)d_offset, &s_val, 8, nullptr);
	}
	catch (const std::exception & ex)
	{
		printf("[RevDll] Failed to set mastery cap: %s\n", ex.what());
	}
}

// set nop [1 byte]
void memory::SetNop(DWORD dwOffset, int nLength)
{
	unsigned char nop = 0x90;
	for (int i = 0; i < nLength; i++) //nlen + 1 ?
	{
		DWORD dCurOffset = (dwOffset + i);
		WriteProcessMemory(this->cur_process, (LPVOID)dCurOffset, &nop, 1, nullptr);
	}
}

//set retn [1 byte]
void memory::SetRetn(DWORD dwOffset)
{
	byte retn = 0xC3;
	WriteProcessMemory(this->cur_process, (LPVOID)dwOffset, &retn, 1, nullptr);
}

//set retn with value on offset [3 bytes]
void memory::SetRetnVal(DWORD dwOffset, byte nValue)
{
	//0xC2 0x04 0x00 = retn in this case, [retn %d]
	byte buf[] = { 0xC2, nValue, 0x00 };
	int size = sizeof(buf) / sizeof(buf[0]);
	WriteProcessMemory(this->cur_process, (LPVOID)dwOffset, &buf, size, nullptr);
}

void memory::SetCmp(DWORD dwOffset, byte nValue)
{
	byte buf[] = { 0x82, 0xF8, nValue };
	int size = sizeof(buf) / sizeof(buf[0]);
	WriteProcessMemory(this->cur_process, (LPVOID)dwOffset, &buf, size, nullptr);
}

void memory::SetJnz(DWORD dwOffset, DWORD dwAddress)
{
	byte jnzInstruction[] = { 0x0F, 0x85 };
	WriteProcessMemory(this->cur_process, (LPVOID)dwOffset, &jnzInstruction, 2, nullptr);
	WriteProcessMemory(this->cur_process, (LPVOID)(dwOffset + 2), &dwAddress, sizeof(DWORD), nullptr);
}

void memory::SetJge(DWORD dwOffset)
{
	byte instruction[] = { 0x7D };
	WriteProcessMemory(this->cur_process, (LPVOID)dwOffset, &instruction, 1, nullptr);
}

void memory::SetJmp(DWORD dwOffset, DWORD dwAddress)
{
	byte jmpInstruction = 0xE9;
	this->WriteByte(dwOffset, 0xE9);
	this->WriteNumber(dwOffset + 1, dwAddress);
	//WriteProcessMemory(this -> cur_process, (LPVOID)(dwOffset + 1), &dwAddress, 4, NULL);
}