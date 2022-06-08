#include "includes.hpp"

int main(int argc, char** argv)
{
	KernelInterface Kernel(L"\\\\.\\my_device");

	ULONG cs_go_proc_id = Kernel.GetCsGoProcessId();

	if (!cs_go_proc_id)
	{
		return 1;
	}

	ULONG_PTR client_dll_addr = Kernel.GetCsGoClientDllAddress();

	if (!client_dll_addr)
	{
		return 1;
	}

	while (!GetAsyncKeyState(VK_END))
	{
		ULONG ent_list = client_dll_addr + offsets::ent_list;

		for (ULONG i = 0; i < 64; ++i)
		{
			ULONG player = 0;
			
			ULONG player_health = 0;
			ULONG player_id		= 0;

			if (!Kernel.KernelReadMemory(cs_go_proc_id, &player, ent_list + ENT_LIST_PLAYER_OFFSET * i, sizeof(ULONG)))
			{
				return 1;
			}

			if (!player)
			{
				continue;
			}

			if (!Kernel.KernelReadMemory(cs_go_proc_id, &player_id, player + offsets::ent::id, sizeof(ULONG)))
			{
				return 1;
			}

			if (!Kernel.KernelReadMemory(cs_go_proc_id, &player_health, player + offsets::ent::healht, sizeof(ULONG)))
			{
				return 1;
			}

			printf("Player id: %d, hp = %d\n", player_id, player_health);
		}

		system("cls");
	}

	system("pause");
}