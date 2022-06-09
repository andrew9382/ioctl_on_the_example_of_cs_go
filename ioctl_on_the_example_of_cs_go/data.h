#pragma once

#include <ntifs.h>

ULONG cs_go_client_dll_address;
ULONG cs_go_process_id;

ULONG controller_process_id;

DEVICE_OBJECT* p_my_device_object;

UNICODE_STRING device_name;
UNICODE_STRING device_sym_link_name;

PVOID ob_callback_handle;