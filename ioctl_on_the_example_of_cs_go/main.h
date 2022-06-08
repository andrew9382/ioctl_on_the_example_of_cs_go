#pragma once

NTSTATUS DriverEntry(DRIVER_OBJECT* p_driver_object, UNICODE_STRING* p_registry_path);

NTSTATUS UnloadDriver(DRIVER_OBJECT* p_driver_object);