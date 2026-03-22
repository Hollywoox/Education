#include <iostream>

using FuncPtr = void (*)();

void (*test())();

class Wrapper {
    FuncPtr ptr_;

public:
    Wrapper(FuncPtr f) : ptr_(f) {}

    FuncPtr operator*() const
    {
        return ptr_;
    }

    operator FuncPtr() const
    {
        return ptr_;
    }
};

void (*test())() 
{
    std::cout << "test\n";
    return reinterpret_cast<FuncPtr>(test);
}

int main() {
    Wrapper function = test();
    (*function)();
    return 0;
}
