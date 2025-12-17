#include <iostream>


class Aboba
{
public :

    void test() const
    {
        std::cout << "Aboba::test\n";
    }
};


template<typename StrategyImpl>
class Entity : public StrategyImpl
{
public :

    void test() const
    {
        StrategyImpl::test();
    }
};


int main()
{
    Entity<Aboba> entity;

    entity.test();

    return 0;
}




