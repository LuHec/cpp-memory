#include <iostream>
#include "allocator.h"

class A
{
private:
    static allocator alloc;

public:
    A(int i) : _i(i) {};
    ~A();

    // void* operator new(size_t size)
    // {
    //     auto p = alloc.allocate(size);
    //     return p;
    // }

    // void operator delete(void* p, size_t size)
    // {
    //     alloc.deallocate(p, size);
    // }

private:
    int _i;
};

allocator A::alloc;

int main()
{
    for(int i = 0; i < 20; i ++)
    {
        A* a = new A(i);
        std::cout << a << " : " << i << std::endl;
    }
}