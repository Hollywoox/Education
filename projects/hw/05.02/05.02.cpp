#include <iostream>


class Entity
{
public :
    virtual ~Entity() = default;

    virtual void test() const = 0;
};


class Client : public virtual Entity
{
public :

    void test() const override
    {
        std::cout << "Client::test\n";
    }
};


class Server : public virtual Entity
{
public :

    void test() const override
    {
        std::cout << "Server::test\n";
    }
};


template<typename D> class Decorator
    : public virtual Entity, public D
{
public :

    using D::D;

    void test() const override
    {
        std::cout << "Decorator::test\n";
        D::test();
    }
};


int main()
{
    Entity * entity_1 = new Client;

    Entity * entity_2 = new Decorator<Client>;

    entity_2->test();

    delete entity_2;
    delete entity_1;
}




