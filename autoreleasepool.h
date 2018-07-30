#ifndef AUTORELEASEPOOL_H
#define AUTORELEASEPOOL_H

#include <vector>
#include <string>
#include "reference.h"
#include "spdefine.h"

class AutoReleasePool
{
public:
    AutoReleasePool();
    AutoReleasePool(const std::string &name);
    ~AutoReleasePool();
    /**
     *  增加引用池对象
     *  @param object:把object增加到引用池
     */
    void AddObject(Reference* object);
    void Clear();
    bool Contains(Reference* object) const;
    void Dump();
    bool IsClearing() const { return isClearing; }

private:
    std::vector<Reference*>  m_vManagedObjectArray;
    std::string              m_sName;
    bool                     isClearing;
};

class PoolManager
{
public:
    static PoolManager* GetPoolManager() { return GetInstance(); }
    static PoolManager* GetInstance();
    static void PurgePoolManager() { DestroyPoolManager(); }
    static void DestroyPoolManager();

    AutoReleasePool* GetCurrentPool() const;
    bool IsObjectInPools(Reference* object) const;

    friend class AutoReleasePool;

private:
    PoolManager();
    ~PoolManager();

    void Push(AutoReleasePool* pool);
    void Pop();

    static PoolManager* s_singleInstance;
    std::vector<AutoReleasePool*>  m_vReleasePoolStack;
};

#endif // AUTORELEASEPOOL_H
