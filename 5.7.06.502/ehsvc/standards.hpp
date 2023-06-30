#pragma once

#pragma comment( linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' \
		version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

/* Undefine UNICODE to disable it */
#ifdef UNICODE
#undef UNICODE
#endif

#ifdef _UNICODE
#undef _UNICODE
#endif

/* Disable secure-warnings */
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _STL_SECURE_NO_WARNINGS
#define _STL_SECURE_NO_WARNINGS
#endif

#include <Windows.h>

#include <CommCtrl.h>
#include <windowsx.h>

#include <iostream>
#include <string>

/* preprocessor macros */
#ifndef Padding
#define Padding(x) struct { unsigned char __padding##x[(x)]; };
#endif

/* 8-byte/64-bit data type */
typedef unsigned long long QWORD;

/* Order-modifiable 8-byte/64-bit data type */
typedef union QUADWORD
{
public:
	QUADWORD(DWORD low, DWORD high) : data32_low(low), data32_high(high)
	{
		/* Constructor */
	};

	QUADWORD(QWORD data) : data64(data)
	{
		/* Constructor */
	};

	/* 8-bit representation */
	BYTE data8[8];

	/* 16-bit representation */
	WORD data16[4];

	/* 32-bit representation */
	DWORD data32[2];

	struct
	{
		DWORD data32_low;
		DWORD data32_high;
	};

	/* 64-bit representation */
	QWORD data64;

} QuadWord, *PQuadWord;