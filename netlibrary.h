#pragma once
#include "event.h"

namespace fx
{
	class NetLibrary
	{
	private:
		char pad_0x0000[0x430];

	public:
		fwEvent<const std::string_view&, const std::string_view&> OnTriggerServerEvent;
	};
}