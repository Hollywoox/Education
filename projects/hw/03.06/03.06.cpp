#include <vector>
#include <iostream>
#include <numbers>
#include <cmath>
#include <memory>


class Shape
{
public:
    virtual ~Shape()
    {
        std::cout << "Shape::~Shape\n";
    }

    virtual double perimeter() const = 0;

    virtual double area() const = 0;
};


class Square final : public Shape
{
public:
    ~Square() override
    {
        std::cout << "Square::~Square\n";
    }

    Square(double sideLength = 0.0) : _sideLength(sideLength) {}

    double perimeter() const override
    {
        return _sideLength * 4;
    }

    double area() const override
    {
        return _sideLength * _sideLength;
    }

private:
    double _sideLength;
};


class Circle final : public Shape
{
public:
    ~Circle() override
    {
        std::cout << "Circle::~Circle\n";
    }

    Circle(double radius = 0.0) : _radius(radius) {}

    double perimeter() const override
    {
        return 2 * std::numbers::pi * _radius;
    }

    double area() const override
    {
        return std::numbers::pi * _radius * _radius;
    }

private:
    double _radius;
};


class Triangle : public Shape
{
public:
    ~Triangle() override
    {
        std::cout << "Triagle::~Triangle\n";
    }

    Triangle(double sideLength_1 = 0.0, double sideLength_2 = 0.0, double sideLength_3 = 0.0) : _sideLength_1(sideLength_1),
                                                                                                _sideLength_2(sideLength_2),
                                                                                                _sideLength_3(sideLength_3)
    {}

    double perimeter() const override final
    {
        return _sideLength_1 + _sideLength_2 + _sideLength_3;
    }

    double area() const override final
    {
        double halfPerimeter = perimeter() / 2;
        return std::sqrt(halfPerimeter * (halfPerimeter - _sideLength_1) * (halfPerimeter - _sideLength_2) * (halfPerimeter - _sideLength_3));
    }

private:
    double _sideLength_1;
    double _sideLength_2;
    double _sideLength_3;
};


int main()
{   
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Square>(5.0));
    shapes.push_back(std::make_unique<Circle>(6.0));
    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0, 5.0));

    std::cout << "Square: perimeter = " << shapes[0]->perimeter() << ", area = " << shapes[0]->area() << "\n";
    std::cout << "Circle: perimeter = " << shapes[1]->perimeter() << ", area = " << shapes[1]->area() << "\n";
    std::cout << "Triangle: perimeter = " << shapes[2]->perimeter() << ", area = " << shapes[2]->area() << "\n";

    return 0;
}