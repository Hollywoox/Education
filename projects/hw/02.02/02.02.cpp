#include <iostream>
#include <cmath>


constexpr double eps = 1e-12;


double calculateDiscriminant(double a, double b, double c)
{
    return b * b - 4 * a * c;
}

void findRoots(double a, double b, double c)
{
    if (std::abs(a) < eps)
    {
        if (std::abs(b) < eps)
        {
            if (std::abs(c) < eps)
            {
                std::cout << "X can be any real number\n";
            }   
            else
            {
                std::cout << "No solution\n";
            }
        }
        else
        {
            double x = -c / b;
            std::cout << "X = " << x << "\n";
        }
    }
    else
    {
        double d = calculateDiscriminant(a, b, c);
        if (std::abs(d) < eps)
        {
            double x = -b / (2 * a);
            std::cout << "X = " << x << "\n";
        }
        else if (d < 0)
        {
            std::cout << "No real roots\n";
        }
        else
        {
            double x1 = (-b + std::sqrt(d)) / (2 * a);
            double x2 = (-b - std::sqrt(d)) / (2 * a);
            std::cout << "X1 = " << x1 << "\n";
            std::cout << "X2 = " << x2 << "\n";
        }
    }
}


int main()
{
    double a, b, c;

    std::cin >> a >> b >> c;

    findRoots(a, b, c);

    return 0;

}