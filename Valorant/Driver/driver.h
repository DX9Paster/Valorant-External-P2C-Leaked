#pragma once
#include <TlHelp32.h>
#include <tchar.h>
#include "../Game/skStr.h"
#include "../Game/globals.hpp"
typedef struct _MEMORY_STRUCT
{
	BYTE type;
	LONG target_pid;
	ULONG64 base_address;
	const char* ModuleName;
	void* address;
	LONG size;
	void* output;

	ULONG_PTR Displacement;
	PVOID Buffer;
	ULONG Size;
	float X = 0.0f, Y = 0.0f;
}MEMORY_STRUCT;

NTSTATUS(*NtUserMessageCall)(HWND hWnd, UINT msg, PVOID wParam, PVOID lParam, ULONG_PTR ResultInfo, DWORD dwType, BOOLEAN bAnsi) = nullptr;
HWND ValidHwnd;
UINT MsgKey;

bool InitHandles() {
	LoadLibraryA(skCrypt("user32.dll"));
	LoadLibraryA(skCrypt("win32u.dll"));
	LoadLibraryA(skCrypt("ntdll.dll"));

	*(PVOID*)&NtUserMessageCall = GetProcAddress(
		GetModuleHandleA(skCrypt("win32u.dll")),
		skCrypt("NtUserMessageCall")
	);
	if (!NtUserMessageCall)
		return false;

	srand(GetTickCount64() * GetCurrentProcessId() * GetCurrentThreadId());
	MsgKey = 0xbd4 + (rand() % 0x1ffff);

	ValidHwnd = FindWindowA(skCrypt("WorkerW"), 0);
	if (INVALID_HANDLE_VALUE != ValidHwnd)
		return true;
	return false;
}

int GetProcessThreadNumByID(DWORD dwPID)
{
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return 0;

	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(pe32);
	BOOL bRet = ::Process32First(hProcessSnap, &pe32);;
	while (bRet)
	{
		if (pe32.th32ProcessID == dwPID)
		{
			::CloseHandle(hProcessSnap);
			return pe32.cntThreads;
		}
		bRet = ::Process32Next(hProcessSnap, &pe32);
	}
	return 0;
}

int GetAowProcId()
{
	DWORD dwRet = 0;
	DWORD dwThreadCountMax = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnapshot, &pe32);
	do
	{
		if (_tcsicmp(pe32.szExeFile, skCrypt(L"VALORANT-Win64-Shipping.exe").decrypt
		()) == 0)

		{
			DWORD dwTmpThreadCount = GetProcessThreadNumByID(pe32.th32ProcessID);

			if (dwTmpThreadCount > dwThreadCountMax)
			{
				dwThreadCountMax = dwTmpThreadCount;
				dwRet = pe32.th32ProcessID;
			}
		}
	} while (Process32Next(hSnapshot, &pe32));
	CloseHandle(hSnapshot);
	return dwRet;
}

DWORD64 GetBaseAddress()
{
	MEMORY_STRUCT memory_struct = { 0 };
	memory_struct.type = 4;
	memory_struct.target_pid = process_id;
	NtUserMessageCall(ValidHwnd, MsgKey, &memory_struct, 0, 0xDEADBEEF, 16, 0);
	return memory_struct.base_address;
}


NTSTATUS ReadProcessMemory(uint64_t src, void* dest, uint32_t size)
{
	MEMORY_STRUCT memory_struct = { 0 };
	memory_struct.type = 2;
	memory_struct.target_pid = process_id;
	memory_struct.address = reinterpret_cast<void*>(src);
	memory_struct.output = dest;
	memory_struct.size = size;
	return NtUserMessageCall(ValidHwnd, MsgKey, &memory_struct, 0, 0xDEADBEEF, 16, 0);
}

bool ReadGuardedRegion(ULONG_PTR Displacement, PVOID pBuffer, ULONG cbBuffer)
{
	BOOL status = TRUE;

	MEMORY_STRUCT memory_struct = { 0 };
	memory_struct.type = 7;

	if (Displacement > 0x200000)
	{
		status = FALSE;
		goto exit;
	}

	RtlSecureZeroMemory(pBuffer, cbBuffer);
	memory_struct.Displacement = Displacement;
	memory_struct.Buffer = pBuffer;
	memory_struct.Size = cbBuffer;
	status = NtUserMessageCall(ValidHwnd, MsgKey, &memory_struct, 0, 0xDEADBEEF, 16, 0);

	if (!status)
	{
		goto exit;
	}

exit:
	return status;
}

template<typename T>
bool Read(DWORD_PTR Address, T* pBuffer, DWORD Size) {

	auto bRead = FALSE;
	auto Rsh_x24 = (Address >> 0x24);
	if (Rsh_x24 == 0x8 || Rsh_x24 == 0x10)
		bRead = ReadGuardedRegion(DWORD_PTR(Address & 0xFFFFFF), (PVOID)pBuffer, sizeof(T));
	else
		bRead = ReadProcessMemory(Address, (PVOID)pBuffer, sizeof(T));
	return bRead;
}

template<typename T>
T Read(DWORD_PTR Address)
{
	T Buffer{};
	Read(Address, &Buffer, sizeof(T));
	return Buffer;
}

template<typename T>
bool Write(uint64_t address, T buffer)
{
	MEMORY_STRUCT memory_struct = { 0 };
	memory_struct.type = 1;
	memory_struct.target_pid = process_id;
	memory_struct.address = reinterpret_cast<void*>(address);
	memory_struct.size = sizeof(T);
	memory_struct.output = &buffer;
	NtUserMessageCall(ValidHwnd, MsgKey, &memory_struct, 0, 0xDEADBEEF, 16, 0);
	return true;
}

void SetGuardedRegion()
{
	MEMORY_STRUCT memory_struct = { 0 };
	memory_struct.type = 6;
	NtUserMessageCall(ValidHwnd, MsgKey, &memory_struct, 0, 0xDEADBEEF, 16, 0);
}
