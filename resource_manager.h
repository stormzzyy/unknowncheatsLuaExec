#pragma once
#include "ref_container.h"
#include "component.h"
#include "event.h"

#include "../include/tbb/concurrent_unordered_map.h"
#include "../include/tbb/concurrent_unordered_set.h"

#include <functional>
#include <mutex>
#include <unordered_map>
#include <optional>
#include "Windows.h"

namespace fx
{
	class Resource;
	class ResourceImpl;
	class ResourceMounter;
	class ResourceManagerImpl;
	class ResourceEventManagerComponent;
	class ResourceEventComponent;

	class ResourceManager : public fwRefCountable, public ComponentHolderImpl<ResourceManager>
	{
	public:
		fwEvent<> OnTick;
		fwEvent<> OnAfterReset;

	public:
		static ResourceManager* getCurrent(bool fb = true);

		static ResourceManagerImpl* getCurrentIl(bool allowFallback = true);

	public:

		template<typename T>
		T* getComp()
		{

			if constexpr (std::is_same_v<T, ResourceEventManagerComponent>)
			{

				return (T*)GetInstanceRegistry()->GetInstance(16).GetRef();
			}

			return 0;
		}
	};

	class ResourceManagerImpl : private ResourceManager
	{
	public:
		std::recursive_mutex m_resourcesMutex;

		std::unordered_map<std::string, fwRefContainer<ResourceImpl>> m_resources;

		std::unordered_multimap<std::string, fwRefContainer<Resource>> m_resourceProvides;

		std::recursive_mutex m_mountersMutex;

		std::vector<fwRefContainer<ResourceMounter>> m_mounters;

	public:
		fwRefContainer<Resource> gResByName(const std::string& name);

		std::vector<fwRefContainer<Resource>> getAllResources();
	};

	class ResourceEventManagerComponent
	{
	private:
		char pad_0x0000[0x290];

	public:
		fwEvent<const std::string&, const std::string&, const std::string&> OnQueueEvent;

	};


}