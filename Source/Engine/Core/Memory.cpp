#include "Memory.h"
#include <iostream>

using namespace std; 

kiko::MemoryTracker kiko::g_memoryTracker;

void* operator new (size_t size)
{
	void* p = malloc(size);

	kiko::g_memoryTracker.Add(p, size);

	

	return p;
}

void operator delete (void* address, size_t size)
{
	kiko::g_memoryTracker.Remove(address, size);
	free(address);

}

namespace kiko
{
	void kiko::MemoryTracker::Add(void* address, size_t size)
	{
		m_bytesAllocated += size;
		m_numAllocations++;
	}

	void kiko::MemoryTracker::Remove(void* address, size_t size)
	{
		m_bytesAllocated -= size;
		m_numAllocations--;
	}

	void kiko::MemoryTracker::DisplayInfo()
	{
		cout << "current bytes allocate: " << m_bytesAllocated << endl;
		cout << "current number allocations: " << m_numAllocations << endl;
	}

}


