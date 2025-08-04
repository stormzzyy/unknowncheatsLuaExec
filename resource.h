#pragma once
#include "event.h"
#include "ref_container.h"
#include "component.h"
#include "omptr.h"

#include "../include/tbb/concurrent_unordered_map.h"
#include "../include/tbb/concurrent_unordered_set.h"

#include <map>
#include <Windows.h>
#include <concurrent_queue.h>


namespace fx
{
	class ResourceManager;
	class ResourceManagerImpl;

	class ResourceMetaDataComponent;
	class ResourceScriptingComponent;

	class IScriptHost;
	class IScriptTickRuntime;
	class IScriptRuntime;

	class ResourceImpl;

	enum ResourceState
	{
		Uninitialized,
		Stopped,
		Starting,
		Started,
		Stopping
	};


	class Resource : public fwRefCountable, public ComponentHolderImpl<Resource>
	{
	public:

		virtual const std::string& GetName() = 0;

	public:

		fwEvent<> UseMemory;
		fwEvent<> UseMemory2;
		fwEvent<std::vector<char>*> Runtime;
		fwEvent<> Start;
		fwEvent<> Stop;

	public:
		ResourceImpl* get_impl();

	};


	class ResourceImpl : public Resource
	{
	public:
		std::string m_name;
		std::string m_rootPath;

		ResourceManagerImpl* m_manager;

		ResourceState m_state;
	};

} // fx
