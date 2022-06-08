#pragma once

#include "includes.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(UNICODE_STRING* image_full_name, HANDLE process_id, IMAGE_INFO* image_info);