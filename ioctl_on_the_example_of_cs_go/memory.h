#pragma once

#include <ntifs.h>

NTSTATUS NTAPI MmCopyVirtualMemory
(
    PEPROCESS SourceProcess,
    PVOID SourceAddress,
    PEPROCESS TargetProcess,
    PVOID TargetAddress,
    SIZE_T BufferSize,
    KPROCESSOR_MODE PreviousMode,
    PSIZE_T ReturnSize
);

NTSTATUS KernelReadVirtualMemory(PEPROCESS process, void* source_address, void* target_address, size_t bytes);

NTSTATUS KernelWriteVirtualMemory(PEPROCESS process, void* source_address, void* target_address, size_t bytes);
