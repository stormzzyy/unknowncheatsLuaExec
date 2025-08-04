#include "resource.h"

#include "../include/xorstr/xorstr.hpp"
#include <format>

namespace fx
{
	ResourceImpl* Resource::get_impl()
	{
		return (ResourceImpl*)&((uint64_t*)this)[0];
	}

} // fx