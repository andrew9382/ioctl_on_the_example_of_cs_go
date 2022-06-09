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

PCREATE_PROCESS_NOTIFY_ROUTINE_EX ProcessCreateCallback(PEPROCESS process, HANDLE process_id, PPS_CREATE_NOTIFY_INFO crt_notify_info)
{
    UNREFERENCED_PARAMETER(process);

    if (crt_notify_info)
    {
        if (wcsstr(crt_notify_info->ImageFileName->Buffer, L"\\user_mode_controller.exe"))
        {
            DebugMsg("user_mode_controller.exe loaded, process id = %d\n", (ULONG)process_id);

            controller_process_id = process_id;
        }
    }

    return STATUS_SUCCESS;
}
