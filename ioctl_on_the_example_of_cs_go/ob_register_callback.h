#pragma once

OB_PREOP_CALLBACK_STATUS ObRegisterCallback(PVOID registration_context, POB_PRE_OPERATION_INFORMATION operation_info);

NTSTATUS RegisterObCallback();