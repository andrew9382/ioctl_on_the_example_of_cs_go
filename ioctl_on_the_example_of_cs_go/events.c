#include "includes.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(UNICODE_STRING* image_full_name, HANDLE process_id, IMAGE_INFO* image_info)
{
    //DebugMsg("Image loaded: %ls\n", image_full_name->Buffer);

    if (wcsstr(image_full_name->Buffer, L"Counter-Strike Global Offensive\\csgo\\bin\\client.dll"))
    {
        DebugMsg("client.dll loaded, process id = %d, address = 0x%X\n", (ULONG)process_id, image_info->ImageBase);

        cs_go_client_dll_address = image_info->ImageBase;
        cs_go_process_id = process_id;
    }

    return STATUS_SUCCESS;
}
