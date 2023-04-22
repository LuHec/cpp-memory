#pragma once 
#include <iostream>

class allocator
{
private:
    struct obj { obj* next; };  // 内嵌指针

public:
    allocator() = default;
    ~allocator()
    {
        while(freeStore != nullptr)
        {
            auto p = freeStore;
            freeStore = freeStore->next;
            free(p);
        }
    }

    void* allocate(size_t size)
    {
        if(freeStore == nullptr)
        {
            size_t chunk = size * CHUNK;
            freeStore = (obj*)malloc(chunk);

            // 把内存切块
            for(int i = 0; i < CHUNK - 1; ++ i)
            {
                freeStore[i].next = &(freeStore[i + 1]);
            }

            freeStore[CHUNK - 1].next = nullptr;
        }

        // 返回第一个可用内存
        auto p = freeStore;
        freeStore = freeStore->next;
        return p;
    }

    void deallocate(void* p, size_t size)
    {
        // 头插法归还内存
        auto p_free = (obj*)p;
        p_free->next = freeStore;
        freeStore = p_free;
    }

private:
    const size_t CHUNK = 5;

private:
    // 存放可用内存
    obj* freeStore = nullptr;
};

