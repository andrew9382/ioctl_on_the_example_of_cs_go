#pragma once

#define PROCESS_QUERY_LIMITED_INFORMATION	0x1000
#define PROCESS_VM_OPERATION				0x0008
#define PROCESS_VM_READ						0x0010
#define PROCESS_VM_WRITE					0x0020
#define PROCESS_TERMINATE					0x0001

#define DebugMsg(x, ...) DbgPrintEx(0, 0, x, __VA_ARGS__)