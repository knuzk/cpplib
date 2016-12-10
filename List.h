// List.h

#pragma once

#include <stddef.h>

template <class T>
class Node
{
public:
    Node();
    Node(size_t offset);

    Node<T>* NextNode();
    Node<T>* PrevNode();

    T* Object();
    T* NextObject();
    T* PrevObject();

    void InsertAfter(T* object);
    void InsertBefore(T* object);
    void Detach();
    bool InList();

private:
    void _Init(size_t offset);
    size_t _Offset();

private:
    T* nextObject;
    Node<T>* prevNode;
};

template <class T>
Node<T>::Node()
{
    this->nextObject = (T*)((size_t)this | 1);
    this->prevNode = this;
}

template <class T>
Node<T>::Node(size_t offset)
{
    _Init(offset);
}

template <class T>
Node<T>* Node<T>::NextNode()
{
    return (Node<T>*)((size_t)this->nextObject + _Offset());
}

template <class T>
Node<T>* Node<T>::PrevNode()
{
    return this->prevNode;
}

template <class T>
T* Node<T>::Object()
{
    return this->PrevNode()->NextObject();
}

template <class T>
T* Node<T>::NextObject()
{
    if ((size_t)this->nextObject & 1)
    {
        return nullptr;
    }

    return this->nextObject;
}

template <class T>
T* Node<T>::PrevObject()
{
    return this->PrevNode()->PrevNode()->NextObject();
}

template <class T>
void Node<T>::InsertAfter(T* object)
{
    auto node = (Node<T>*)((size_t)object + _Offset());
    node->nextObject = this->nextObject;
    node->prevNode = this;
    this->NextNode()->prevNode = node;
    this->nextObject = object;
}

template <class T>
void Node<T>::InsertBefore(T* object)
{
    auto node = (Node<T>*)((size_t)object + _Offset());
    node->nextObject = this->Object();    
    node->prevNode = this->PrevNode();
    this->PrevNode()->nextObject = object;
    this->prevNode = node;
}

template <class T>
void Node<T>::Detach()
{
    auto offset = _Offset();
    auto prevNode = this->PrevNode();
    auto nextNode = this->NextNode();
    prevNode->nextObject = this->nextObject;
    nextNode->prevNode = prevNode;
    _Init(offset);
}

template <class T>
bool Node<T>::InList()
{
    return this != this->prevNode;
}

template <class T>
void Node<T>::_Init(size_t offset)
{
    this->nextObject = (T*)((size_t)this - offset);
    this->prevNode = this;
}

template <class T>
size_t Node<T>::_Offset()
{
    return (size_t)this - (size_t)this->prevNode->nextObject;
}

template <class T>
class List
{
public:
    List(size_t offset);

    Node<T>* First();
    Node<T>* Last();

    Node<T>* Begin();
    Node<T>* End();

    bool Empty();
    void Clear();

    List<T>& Append(T* object);
    List<T>& InsertFirst(T* object);

private:
    Node<T> head;
};

template <class T>
List<T>::List(size_t offset)
: head(offset)
{
}

template <class T>
Node<T>* List<T>::First()
{
    return this->head.NextNode();
}

template <class T>
Node<T>* List<T>::Last()
{
    return this->head.PrevNode();
}

template <class T>
Node<T>* List<T>::Begin()
{
    return this->First();
}

template <class T>
Node<T>* List<T>::End()
{
    return &this->head;
}

template <class T>
bool List<T>::Empty()
{
    return !this->head.InList();
}

template <class T>
void List<T>::Clear()
{
    this->head.Detach();
}

template <class T>
List<T>& List<T>::Append(T* object)
{
    this->head.InsertBefore(object);
    return *this;
}

template <class T>
List<T>& List<T>::InsertFirst(T* object)
{
    this->head.InsertAfter(object);
    return *this;
}