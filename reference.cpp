#include "reference.h"
#include "autoreleasepool.h"

Reference::Reference():m_iReferenceCount(1)
{

}

Reference::~Reference()
{

}

void Reference::Retain()
{
    ++m_iReferenceCount;
}

void Reference::Release()
{
    --m_iReferenceCount;
    if (m_iReferenceCount == 0) {
#if defined(GRAPH_DEBUG) && (GRAPH_DEBUG > 0)
        auto poolManager = PoolManager::GetInstance();
        if (!poolManager->GetCurrentPool()->IsClearing() && poolManager->IsObjectInPools(this))
        {
            ASSERT(false, "The reference shouldn't be 0 because it is still in autorelease pool.");
        }
#endif
        delete this;
    }
}

Reference* Reference::AutoReleasse()
{
    PoolManager::GetInstance()->GetCurrentPool()->AddObject(this);
    return this;
}

unsigned int Reference::GetReferenceCount() const
{
    return m_iReferenceCount;
}


