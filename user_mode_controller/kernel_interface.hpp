#pragma once

class KernelInterface
{
private:

	HANDLE h_driver;

public:

	KernelInterface(const wchar_t* registry_path);

	ULONG_PTR GetCsGoClientDllAddress();

	ULONG GetCsGoProcessId();

	bool KernelReadMemory(ULONG process_id, PVOID buffer, ULONG address, SIZE_T size);

	bool KernelWriteMemory(ULONG process_id, PVOID buffer, ULONG address, SIZE_T size);
};