#include "includes.h"

NTSTATUS DriverEntry(DRIVER_OBJECT* p_driver_object, UNICODE_STRING* p_registry_path)
{
	UNREFERENCED_PARAMETER(p_driver_object);
	UNREFERENCED_PARAMETER(p_registry_path);

	DebugMsg("Driver loaded.\n");

	p_driver_object->DriverUnload = UnloadDriver;

	p_driver_object->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	p_driver_object->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	p_driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

	PsSetLoadImageNotifyRoutine(ImageLoadCallback);

	RtlInitUnicodeString(&device_name, L"\\Device\\my_device");
	RtlInitUnicodeString(&device_sym_link_name, L"\\DosDevices\\my_device");

	NTSTATUS status = IoCreateDevice(p_driver_object, 0, &device_name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &p_my_device_object);

	if (!NT_SUCCESS(status))
	{
		DebugMsg("IoCreateDevice failed with status: 0x%X\n", status);

		return status;
	}

	status = IoCreateSymbolicLink(&device_sym_link_name, &device_name);

	if (!NT_SUCCESS(status))
	{
		DebugMsg("IoCreateSymbolicLink failed with status: 0x%X\n", status);

		return status;
	}

	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(DRIVER_OBJECT* p_driver_object)
{
	UNREFERENCED_PARAMETER(p_driver_object);

	DebugMsg("Driver unloaded.");
	
	PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);

	IoDeleteDevice(p_driver_object->DeviceObject);
	IoDeleteSymbolicLink(&device_sym_link_name);

	return STATUS_SUCCESS;
}