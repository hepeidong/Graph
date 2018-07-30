#include "autoreleasepool.h"

AutoReleasePool::AutoReleasePool():m_sName("")
#if defined(GRAPH_DEBUG) && (GRAPH_DEBUG > 0)
  ,isClearing(false)
#endif
{
    m_vManagedObjectArray.reserve(150);
    PoolManager::GetInstance()->Push(this);
}

AutoReleasePool::AutoReleasePool(const std::string &name):m_sName(name)
#if defined(GRAPH_DEBUG) && (GRAPH_DEBUG > 0)
  ,isClearing(false)
#endif
{
    m_vManagedObjectArray.reserve(150);
    PoolManager::GetInstance()->Push(this);
}

AutoReleasePool::~AutoReleasePool()
{
    Clear();
    PoolManager::GetInstance()->Pop();
}

void AutoReleasePool::AddObject(Reference *object)
{
    m_vManagedObjectArray.push_back(object);
}

void AutoReleasePool::Clear()
{
#if defined(GRAPH_DEBUG) && (GRAPH_DEBUG > 0)
    isClearing = true;
#endif
    for (const auto &obj : m_vManagedObjectArray)
    {
        obj->Release();
    }
    m_vManagedObjectArray.clear();
#if defined(GRAPH_DEBUG) && (GRAPH_DEBUG > 0)
    isClearing = false;
#endif
}

bool AutoReleasePool::Contains(Reference *object) const
{
    for (const auto &obj : m_vManagedObjectArray)
    {
        if (obj == object)
        {
            return true;
        }
    }
    return false;
}


void AutoReleasePool::Dump()
{
    DEBUGMSG("autorelease pool: %s, number of managed object %d\n", m_sName.c_str(), static_cast<int>(m_vManagedObjectArray.size()));
    DEBUGMSG("%20s%20s%20s", "Object pointer", "Object id", "reference count");
    for (const auto &obj : m_vManagedObjectArray)
    {
        UNUSED_PARAM(obj);
        DEBUGMSG("%20p%20u\n", obj, obj->GetReferenceCount());
    }
}

//PoolManager
PoolManager* PoolManager::s_singleInstance = nullptr;
PoolManager* PoolManager::GetInstance()
{
    if (s_singleInstance == nullptr)
    {
        s_singleInstance = new (std::nothrow) PoolManager();
        new AutoReleasePool("ALGraph autorelease pool");
    }
    return s_singleInstance;
}

void PoolManager::DestroyPoolManager()
{
    delete s_singleInstance;
    s_singleInstance = nullptr;
}

PoolManager::PoolManager()
{
    m_vReleasePoolStack.reserve(10);
}

PoolManager::~PoolManager()
{
    DEBUGMSG("deallocing PoolManager: %p", this);
    while(!m_vReleasePoolStack.empty())
    {
        AutoReleasePool *pool = m_vReleasePoolStack.back();
        delete pool;
    }
}

AutoReleasePool* PoolManager::GetCurrentPool() const
{
    return m_vReleasePoolStack.back();
}

bool PoolManager::IsObjectInPools(Reference *object) const
{
    for (const auto& pool : m_vReleasePoolStack)
    {
        if (pool->Contains(object))
            return true;
    }
    return false;
}

void PoolManager::Push(AutoReleasePool *pool)
{
    m_vReleasePoolStack.push_back(pool);
}

void PoolManager::Pop()
{
    ASSERT(!m_vReleasePoolStack.empty(), " ");
    m_vReleasePoolStack.pop_back();
}



