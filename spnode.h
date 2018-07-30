#ifndef SPNODE_H
#define SPNODE_H

#include "pos.h"
#include "reference.h"

template<typename Tp>
class Node : public Reference
{
public:
    typedef Tp value_t;

public:
    Node();
    virtual ~Node();

    virtual int GetPosition() const;
    virtual float GetPosition() const;
    virtual void AddChild();
    virtual void RemoveChild();
    virtual Node<Tp> FindNode(int x, int y);
    virtual Node<Tp> FindNode(float x, float y);
    virtual Node<Tp> FindNode(value_t d);
};


#endif // SPNODE_H
