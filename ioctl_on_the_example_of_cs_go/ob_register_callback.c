#include "includes.h"

OB_PREOP_CALLBACK_STATUS ObRegisterCallback(PVOID registration_context, POB_PRE_OPERATION_INFORMATION operation_info)
{
    UNREFERENCED_PARAMETER(registration_context);

    PEPROCESS opened_process = (PEPROCESS)operation_info->Object;

    ULONG opened_process_id = PsGetProcessId(opened_process);

    if (controller_process_id)
    {
        if (controller_process_id == opened_process_id)
        {
            if (operation_info->KernelHandle)
            {
                return OB_PREOP_SUCCESS;
            }

            if (operation_info->Operation == OB_OPERATION_HANDLE_CREATE)
            {
                if (operation_info->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_QUERY_LIMITED_INFORMATION)
                {
                    DebugMsg("ObRegisterCallback: handle stripped from PROCESS_QUERY_LIMITED_INFORMATION rights!\n");

                    operation_info->Parameters->CreateHandleInformation.DesiredAccess ^= PROCESS_QUERY_LIMITED_INFORMATION;
                }
                else if (operation_info->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_READ)
                {
                    DebugMsg("ObRegisterCallback: handle stripped from PROCESS_VM_READ rights!\n");
                    
                    operation_info->Parameters->CreateHandleInformation.DesiredAccess ^= PROCESS_VM_READ;
                }
            }
            else if (operation_info->Operation == OB_OPERATION_HANDLE_DUPLICATE)
            {
                if (operation_info->Parameters->DuplicateHandleInformation.OriginalDesiredAccess & PROCESS_QUERY_LIMITED_INFORMATION)
                {
                    DebugMsg("ObRegisterCallback: handle stripped from PROCESS_QUERY_LIMITED_INFORMATION rights!\n");
                    
                    operation_info->Parameters->DuplicateHandleInformation.DesiredAccess ^= PROCESS_QUERY_LIMITED_INFORMATION;
                }
                else if (operation_info->Parameters->DuplicateHandleInformation.OriginalDesiredAccess & PROCESS_VM_READ)
                {
                    DebugMsg("ObRegisterCallback: handle stripped from PROCESS_VM_READ rights!\n");
                    
                    operation_info->Parameters->DuplicateHandleInformation.DesiredAccess ^= PROCESS_VM_READ;
                }
            }
        }
    }

    return OB_PREOP_SUCCESS;
}

NTSTATUS RegisterObCallback()
{
    OB_CALLBACK_REGISTRATION callback_reg;
    OB_OPERATION_REGISTRATION operation_reg;

    memset(&callback_reg, 0, sizeof(OB_CALLBACK_REGISTRATION));
    memset(&operation_reg, 0, sizeof(OB_OPERATION_REGISTRATION));

    RtlInitUnicodeString(&callback_reg.Altitude, L"CallBack");

    callback_reg.Version = ObGetFilterVersion();
    callback_reg.OperationRegistration = &operation_reg;
    callback_reg.OperationRegistrationCount = 1;

    operation_reg.ObjectType = PsProcessType;
    operation_reg.Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;
    operation_reg.PreOperation = ObRegisterCallback;

    return ObRegisterCallbacks(&callback_reg, &ob_callback_handle);
}
