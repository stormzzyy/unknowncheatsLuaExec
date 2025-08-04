#include "component.h"

#include "../include/xorstr/xorstr.hpp"

#include <Windows.h>


namespace fx
{
	ComponentRegistryImpl* ComponentRegistry::get_impl()
	{
		static ComponentRegistryImpl* (*CoreGetComponentRegistry)() =
			reinterpret_cast<decltype(CoreGetComponentRegistry)>(
				reinterpret_cast<uintptr_t>(GetModuleHandleA("CoreRT.dll")) + 0x43af0
				);

		return CoreGetComponentRegistry();
	}
} // fx 

//CoreRT.dll