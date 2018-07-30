#include "vertex.h"
#include <algorithm>

template<typename Tp>
Vertex<Tp>::Vertex()
{

}

template<typename Tp>
Vertex<Tp>::~Vertex()
{

}

template<typename Tp>
Vertex<Tp>* Vertex<Tp>::CreateVertex(value_t info)
{
    Vertex<Tp>* ver = new (std::nothrow) Vertex();
    if (ver->InitVertex(info))
    {
        ver->AutoReleasse();
    }
    else
    {
        SAFE_DELETE(ver);
    }
    return ver;
}

template<typename Tp>
bool Vertex<Tp>::InitVertex(value_t info)
{
    m_vertexInfo = info;
    return true;
}

template<typename Tp>
void Vertex<Tp>::SetVertexInfo(value_t info)
{
    m_vertexInfo = info;
}

template<typename Tp>
inline typename Vertex<Tp>::value_t Vertex<Tp>::GetVertexInfo() const
{
    return m_vertexInfo;
}

template<typename Tp>
bool Vertex<Tp>::AppendEdge(value_t info, site_t weight)
{
    edge_t* p = first_edge;
    edge_t* q = NULL;
    while (p) {
        if (p->GetAdjVertex() == info) return false;
        q = p;
        p = p->next_edge;
    }
    p = Arc<Tp>::CreateArc(weight, info);
    if (q == NULL)
        first_edge = p;
    else
        q->next_edge = p;
    return true;
}

template<typename Tp>
void Vertex<Tp>::ClearEdgeList()
{
    edge_t* p;
    edge_t* q;
    p = first_edge;
    while (p) {
        q = p->next_edge;
        delete p;
        p = q;
    }
    first_edge = NULL;
}
