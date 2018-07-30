#ifndef VERTEX_H
#define VERTEX_H

#include "reference.h"
#include "arc.h"

template<typename Tp>
class Vertex : public Reference
{
public:
    typedef Arc<Tp> edge_t;
    typedef typename Arc<Tp>::arc_t value_t;
    typedef typename Arc<Tp>::site_t site_t;

private:
    Vertex();
    ~Vertex();
    bool InitVertex(value_t info);

public:
    static Vertex<Tp>* CreateVertex(value_t info);
    void SetVertexInfo(value_t info);
    value_t GetVertexInfo() const;
    bool AppendEdge(value_t info, site_t weight);
    void ClearEdgeList();

private:
    value_t m_vertexInfo;

public:
    edge_t* first_edge;
};

#endif // VERTEX_H
