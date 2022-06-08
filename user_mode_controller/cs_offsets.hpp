#pragma once

#include <Windows.h>

#define ENT_LIST_PLAYER_OFFSET 0x10

namespace offsets
{
	inline ULONG ent_list = 0x4DD7B1C; // client.dll

	namespace ent
	{
		inline ULONG id = 0x64;
		inline ULONG healht	= 0x100;
	}
}