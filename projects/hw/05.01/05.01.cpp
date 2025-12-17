#include <string>


class Person
{
public :

    Person(const std::string& name, int age, int grade)
        : m_name(name), m_age(age), m_grade(grade)
    {
    }


    const std::string& name() const { return m_name; }

    int age() const { return m_age; }

    int grade() const { return m_grade; }

private :

    std::string m_name;
    int m_age = 0;
    int m_grade = 0;
};


class Builder
{
public :

    Builder() = default;

    Builder& name(const std::string& name)
    {
        m_name = name;
        return *this;
    }

    Builder& age(int age)
    {
        m_age = age;
        return *this;
    }

    Builder& grade(int grade)
    {
        m_grade = grade;
        return *this;
    }

    Person get() const
    {
        return Person(m_name, m_age, m_grade);
    }

private :

    std::string m_name;
    int m_age = 0;
    int m_grade = 0;
};


int main()
{
    Builder builder;

    auto person = builder.name("Ivan").age(25).grade(10).get();

    static_assert(std::is_same_v<decltype(person), Person>);
}


