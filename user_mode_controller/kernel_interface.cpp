#include "includes.hpp"

KernelInterface::KernelInterface(const wchar_t* registry_path)
{
	h_driver = CreateFile(registry_path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
}

ULONG_PTR KernelInterface::GetCsGoClientDllAddress()
{
	if (h_driver == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	ULONG_PTR address = 0;

	if (!DeviceIoControl(h_driver, IO_GET_CLIENT_DLL_ADDRESS, &address, sizeof(address), &address, sizeof(address), 0, 0))
	{
		return 0;
	}

	return address;
}

ULONG KernelInterface::GetCsGoProcessId()
{
	if (h_driver == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	ULONG proc_id = 0;

	if (!DeviceIoControl(h_driver, IO_GET_CS_PROCESS_ID, &proc_id, sizeof(proc_id), &proc_id, sizeof(proc_id), 0, 0))
	{
		return 0;
	}

	return proc_id;
}

bool KernelInterface::KernelReadMemory(ULONG process_id, PVOID buffer, ULONG address, SIZE_T size)
{
	if (h_driver == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	if (!buffer)
	{
		return false;
	}

	KERNEL_READ_VIRTUAL_MEMORY kernel_read_v_mem;
	
	kernel_read_v_mem.process_id = process_id;
	kernel_read_v_mem.address = address;
	kernel_read_v_mem.p_buffer = buffer;
	kernel_read_v_mem.size = size;

	if (!DeviceIoControl(h_driver, IO_READ_MEMORY_REQUEST, &kernel_read_v_mem, sizeof(KERNEL_READ_VIRTUAL_MEMORY), &kernel_read_v_mem, sizeof(KERNEL_READ_VIRTUAL_MEMORY), 0, 0))
	{
		return false;
	}
}

bool KernelInterface::KernelWriteMemory(ULONG process_id, PVOID buffer, ULONG address, SIZE_T size)
{
	if (h_driver == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	if (!buffer)
	{
		return false;
	}

	KERNEL_WRITE_VIRTUAL_MEMORY kernel_write_v_mem;

	kernel_write_v_mem.process_id = process_id;
	kernel_write_v_mem.address = address;
	kernel_write_v_mem.p_buffer = buffer;
	kernel_write_v_mem.size = size;

	if (!DeviceIoControl(h_driver, IO_WRITE_MEMORY_REQUEST, &kernel_write_v_mem, sizeof(KERNEL_WRITE_VIRTUAL_MEMORY), &kernel_write_v_mem, sizeof(KERNEL_WRITE_VIRTUAL_MEMORY), 0, 0))
	{
		return false;
	}
}