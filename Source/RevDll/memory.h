#pragma once
#include <thread>
#include <Windows.h>

class memory
{
public:
	memory();
	~memory();

	void WriteNumber(DWORD d_offset, DWORD d_val);
	void WriteByte(DWORD d_offset, DWORD d_byte);
	void WriteString(DWORD d_offset, char* s_val);
	void WriteDouble(DWORD d_offset, DOUBLE s_val);
	void SetNop(DWORD d_offset, int nLength);
	void SetRetn(DWORD d_offset);
	void SetRetnVal(DWORD d_offset, byte nValue);
	void SetCmp(DWORD dwOffset, byte nValue);
	void SetJnz(DWORD dwOffset, DWORD dwAddress);
	void SetJge(DWORD dwOffset);
	void SetJmp(DWORD dwOffset, DWORD dwAddress);

private:
	HANDLE cur_process;
};
