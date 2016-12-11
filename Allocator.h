// Allocator.h

#pragma once

#include <vector>
#include "List.h"

template <class T, size_t PoolIncreaseStep = 1024>
class Allocator
{
public:
    Allocator(size_t offset);
    ~Allocator();

    void Clear();
    void Recycle();

    T* Allocate();
    void Deallocate(T* object);

private:
    void _AllocateFree(size_t size);
    void _AppendFree(T* newItems, size_t size);

private:
    std::vector<T*> pool;
    List<T> freeList;
};

template <class T, size_t PoolIncreaseStep>
Allocator<T, PoolIncreaseStep>::Allocator(size_t offset)
: freeList(offset)
{
}

template <class T, size_t PoolIncreaseStep>
Allocator<T, PoolIncreaseStep>::~Allocator()
{
    Clear();
}

template <class T, size_t PoolIncreaseStep>
void Allocator<T, PoolIncreaseStep>::Clear()
{
    this->freeList.Clear();
    for (auto i : this->pool)
    {
        delete[] i;
    }
    this->pool.clear();
}

template <class T, size_t PoolIncreaseStep>
void Allocator<T, PoolIncreaseStep>::Recycle()
{
    this->freeList.Clear();
    for (auto i : this->pool)
    {
        _AppendFree(i, PoolIncreaseStep);
    }
}

template <class T, size_t PoolIncreaseStep>
T* Allocator<T, PoolIncreaseStep>::Allocate()
{
    if (this->freeList.Empty())
    {
        _AllocateFree(PoolIncreaseStep);
    }

    auto first = this->freeList.First();
    first->Detach();
    return first->Object();
}

template <class T, size_t PoolIncreaseStep>
void Allocator<T, PoolIncreaseStep>::Deallocate(T* object)
{
    this->freeList.InsertFirst(object);
}

template <class T, size_t PoolIncreaseStep>
void Allocator<T, PoolIncreaseStep>::_AllocateFree(size_t size)
{
    auto newItems = new T[size];
    this->pool.push_back(newItems);
    _AppendFree(newItems, size);
}

template <class T, size_t PoolIncreaseStep>
void Allocator<T, PoolIncreaseStep>::_AppendFree(T* newItems, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        this->freeList.Append(&newItems[i]);
    }
}
