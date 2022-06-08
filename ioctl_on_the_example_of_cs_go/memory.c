#include "memory.h"

NTSTATUS KernelReadVirtualMemory(PEPROCESS process, void* source_address, void* target_address, size_t bytes)
{
    SIZE_T out_bytes;

    return MmCopyVirtualMemory(process, source_address, PsGetCurrentProcess(), target_address, bytes, KernelMode, &out_bytes);
}

NTSTATUS KernelWriteVirtualMemory(PEPROCESS process, void* source_address, void* target_address, size_t bytes)
{
    SIZE_T out_bytes;

    return MmCopyVirtualMemory(PsGetCurrentProcess(), source_address, process, target_address, bytes, KernelMode, &out_bytes);
}
