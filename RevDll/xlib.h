#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>
#include <vector>
#include <assert.h>
#include <string>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

#define X_DEBUG TRUE

//Assembly mnemonics
#define ASM_NOP 0x90
#define ASM_JMP 0xE9 //LONG
#define ASM_CALL 0xE8 //LONG