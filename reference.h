#ifndef REFERENCE_H
#define REFERENCE_H

#include "spdefine.h"

class Reference
{
protected:
    Reference();

public:
    virtual ~Reference();

    void Retain(void);
    void Release(void);
    Reference* AutoReleasse();
    unsigned int GetReferenceCount() const;

protected:
    unsigned int m_iReferenceCount;

    friend class AutoReleassePool;
};

#endif // REFERENCE_H
