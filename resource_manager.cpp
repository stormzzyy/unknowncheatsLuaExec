#include "resource_manager.h"
#include "resource.h"

#include "../include/xorstr/xorstr.hpp"

#include <Windows.h>

namespace fx
{
	ResourceManager* ResourceManager::getCurrent(bool fb)
	{

		static ResourceManager* (*GetCurrent)(bool allowFallback) =
			reinterpret_cast<decltype(GetCurrent)>(
				reinterpret_cast<uintptr_t>(GetModuleHandleA("citizen-resources-core.dll")) + 0x24ae0
				);

		return GetCurrent(fb);
	}

	ResourceManagerImpl* ResourceManager::getCurrentIl(bool fb)
	{
		return (ResourceManagerImpl*)&((uint64_t*)getCurrent(fb))[2];
	}

	fwRefContainer<Resource> ResourceManagerImpl::gResByName(const std::string& name)
	{
		std::unique_lock<std::recursive_mutex> lock(m_resourcesMutex);

		fwRefContainer<Resource> resource;

		auto it = m_resources.find(name);
		if (it != m_resources.end())
			resource = it->second;

		return resource;
	}

	std::vector<fwRefContainer<Resource>> ResourceManagerImpl::getAllResources()
	{
		std::vector<fwRefContainer<Resource>> resources;

		for (auto& resource : m_resources)
			resources.push_back(resource.second);

		return resources;
	}

} // fx