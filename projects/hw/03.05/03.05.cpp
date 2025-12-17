/////////////////////////////////////////////////////////////

#include <print>
#include <vector>
#include <iostream>

/////////////////////////////////////////////////////////////

class Entity_v1 
{
public :

// ~Entity() = default; // error

//  ------------------------------------

	virtual ~Entity_v1()
	{
		std::cout << "Entity_v1::~Entity_v1\n";
	}

//  ------------------------------------

	virtual void test() const
	{ 
		std::cout << "Entity_v1::test\n";
	}
};

/////////////////////////////////////////////////////////////

class Entity_v2 
{
public :

// ~Entity() = default; // error

//  ------------------------------------

	virtual ~Entity_v2()
	{
		std::cout << "Entity_v2::~Entity_v2\n";
	}

//  ------------------------------------

	virtual void test() const
	{ 
		std::cout << "Entity_v2::test\n";
	}
};

/////////////////////////////////////////////////////////////


class Adapter_v1 : public Entity_v1
{
public:

    virtual ~Adapter_v1()
    {
        std::cout << "Adapter_v1::~Adapter_v1\n";
    }

    virtual void test_v1() const
    {
        std::cout << "Adapter_v1::test\n";
        test();
    }

    void test() const override 
    {
        std::cout << "Adapter_v1::test_v1, redirection to test_v1\n";
        test_v1();
    }

};

/////////////////////////////////////////////////////////////

class Adapter_v2 : public Entity_v2
{
public:

    virtual ~Adapter_v2()
    {
        std::cout << "Adapter_v2::~Adapter_v2\n";
    }

    virtual void test_v2() const
    {
        std::cout << "Adapter_v2::test\n";
        test();
    }

    void test() const override 
    {
        std::cout << "Adapter_v2::test_v2, redirection to test_v2\n";
        test_v2();
    }

};

/////////////////////////////////////////////////////////////

class Client : public Adapter_v1, public Adapter_v2
{
public :

   ~Client() override
	{
		std::cout << "Client::~Client\n";
	}

//  ------------------------------------

	void test_v1() const override final
	{ 
		std::cout << "Client::test_v1\n";
	}

    void test_v2() const override final
	{ 
		std::cout << "Client::test_v2\n";
	}

    void test() const override final
    {
		std::cout << "Client::test\n";
    }

};



int main()
{
    Client client;
    client.test_v1();

    std::cout << "-------\n";

    client.Adapter_v1::test_v1();

    std::cout << "-------\n";

    client.Adapter_v2::test_v2();
    
    std::cout << "-------\n";

    client.Entity_v1::test();

    std::cout << "-------\n";

    client.Entity_v2::test();

    std::cout << "-------\n";

    return 0;
}

/////////////////////////////////////////////////////////////x