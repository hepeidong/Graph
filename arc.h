#ifndef ARC_H
#define ARC_H

#include "reference.h"

template<typename Tp>
class Arc : public Reference
{
public:
    typedef Tp value_t;
    typedef int site_t;

private:
    Arc();
    ~Arc();
    virtual bool InitArc(value_t weight, site_t adjVertex = -1);

public:
    static Arc<Tp>* CreateArc(value_t weight, site_t adjVertex = -1);
    virtual void SetAdjVertex(site_t adjVertex);
    virtual site_t GetAdjVertex() const;
    virtual void SetWeight(value_t weight);
    virtual value_t GetWeight() const;

private:
    site_t m_adjVertex;
    value_t m_weight;

public:
    Arc<Tp>* next_edge;
};

#endif // ARC_H
