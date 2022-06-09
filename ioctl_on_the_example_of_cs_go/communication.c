#include "includes.h"

NTSTATUS IoControl(DEVICE_OBJECT* p_device_object, IRP* p_irp)
{
    UNREFERENCED_PARAMETER(p_device_object);

    NTSTATUS status = STATUS_UNSUCCESSFUL;
    ULONG bytes_io = 0;

    // стак который используется для передачи данных между драйвером и прогой в юзер моде
    IO_STACK_LOCATION* p_io_stack = IoGetCurrentIrpStackLocation(p_irp);

    // код который получаем от юзермода
    ULONG io_control_code = p_io_stack->Parameters.DeviceIoControl.IoControlCode;

    if (io_control_code == IO_GET_CLIENT_DLL_ADDRESS)
    {
        ULONG* p_output_buffer = (ULONG*)p_irp->AssociatedIrp.SystemBuffer;
        *p_output_buffer = cs_go_client_dll_address;

        DebugMsg("IoControl: client.dll address requested!\n");

        status = STATUS_SUCCESS;
        bytes_io = sizeof(ULONG);
    }
    else if (io_control_code == IO_GET_CS_PROCESS_ID)
    {
        ULONG* p_output_buffer = (ULONG*)p_irp->AssociatedIrp.SystemBuffer;
        *p_output_buffer = cs_go_process_id;

        DebugMsg("IoControl: Cs Go process id requested!\n");

        status = STATUS_SUCCESS;
        bytes_io = sizeof(ULONG);
    }
    else if (io_control_code == IO_READ_MEMORY_REQUEST)
    {
        KERNEL_READ_VIRTUAL_MEMORY* p_output_buffer = (KERNEL_READ_VIRTUAL_MEMORY*)p_irp->AssociatedIrp.SystemBuffer;
        
        PEPROCESS process;

        if (NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)p_output_buffer->process_id, &process)))
        {
            if (NT_SUCCESS(KernelReadVirtualMemory(process, p_output_buffer->address, p_output_buffer->p_buffer, p_output_buffer->size)))
            {
                status = STATUS_SUCCESS;
                bytes_io = sizeof(KERNEL_READ_VIRTUAL_MEMORY);
            }
        }
    }
    else if (io_control_code == IO_WRITE_MEMORY_REQUEST)
    {
        KERNEL_WRITE_VIRTUAL_MEMORY* p_output_buffer = (KERNEL_WRITE_VIRTUAL_MEMORY*)p_irp->AssociatedIrp.SystemBuffer;

        PEPROCESS process;

        if (NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)p_output_buffer->process_id, &process)))
        {
            if (NT_SUCCESS(KernelWriteVirtualMemory(process, p_output_buffer->p_buffer, p_output_buffer->address, p_output_buffer->size)))
            {
                status = STATUS_SUCCESS;
                bytes_io = sizeof(KERNEL_WRITE_VIRTUAL_MEMORY);
            }
        }
    }

    p_irp->IoStatus.Status = status;
    p_irp->IoStatus.Information = bytes_io;

    IoCompleteRequest(p_irp, IO_NO_INCREMENT);

    return status;
}

NTSTATUS CloseCall(DEVICE_OBJECT* p_device_object, IRP* p_irp)
{
    UNREFERENCED_PARAMETER(p_device_object);

    p_irp->IoStatus.Status = STATUS_SUCCESS;
    p_irp->IoStatus.Information = 0;

    IoCompleteRequest(p_irp, IO_NO_INCREMENT);

    DebugMsg("CloseCall was called, connection closed!\n");

    return STATUS_SUCCESS;
}

NTSTATUS CreateCall(DEVICE_OBJECT* p_device_object, IRP* p_irp)
{
    UNREFERENCED_PARAMETER(p_device_object);

    p_irp->IoStatus.Status = STATUS_SUCCESS;
    p_irp->IoStatus.Information = 0;

    IoCompleteRequest(p_irp, IO_NO_INCREMENT);

    return STATUS_SUCCESS;
}