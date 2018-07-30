#include "arc.h"
#include <algorithm>

template<typename Tp>
Arc<Tp>::Arc():m_adjVertex(-1)
{

}

template<typename Tp>
Arc<Tp>::~Arc()
{

}

template<typename Tp>
Arc<Tp>* Arc<Tp>::CreateArc(value_t weight, site_t adjVertex)
{
    Arc<Tp>* arc = new (std::nothrow) Arc();
    if (arc->InitArc(weight, adjVertex))
    {
        arc->AutoReleasse();
    }
    else
    {
        SAFE_DELETE(arc);
    }
    return arc;
}

template<typename Tp>
bool Arc<Tp>::InitArc(value_t weight, site_t adjVertex)
{
    m_weight = weight;
    m_adjVertex = adjVertex;
    return true;
}

template<typename Tp>
void Arc<Tp>::SetAdjVertex(site_t adjVertex)
{
    m_adjVertex = adjVertex;
}

template<typename Tp>
inline typename Arc<Tp>::site_t Arc<Tp>::GetAdjVertex() const
{
    return m_adjVertex;
}

template<typename Tp>
void Arc<Tp>::SetWeight(value_t weight)
{
    m_weight = weight;
}

template<typename Tp>
inline typename Arc<Tp>::value_t Arc<Tp>::GetWeight() const
{
    return m_weight;
}
