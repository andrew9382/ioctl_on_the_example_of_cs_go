#pragma once

#include "includes.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(UNICODE_STRING* image_full_name, HANDLE process_id, IMAGE_INFO* image_info);

PCREATE_PROCESS_NOTIFY_ROUTINE_EX ProcessCreateCallback(PEPROCESS process, HANDLE process_id, PPS_CREATE_NOTIFY_INFO crt_notify_info);