#include <iostream>
#include <cmath>


int main()
{
    double epsilon;
    std::cin >> epsilon;

    double pi = 0.0;
    int n = 0;
    double term = 1.0;
    
    while (std::abs(term) >= epsilon)
    {
        pi += term;
        n++;
        term = (n % 2 == 0 ? 1.0 : -1.0) / (2.0 * n + 1.0);
    }
    pi *= 4.0;

    double e = 0.0;
    n = 0;
    term = 1.0;
    
    while (std::abs(term) >= epsilon)
    {
        e += term;
        n++;
        term = term / static_cast<double>(n);
    }

    std::cout << pi << "\n";
    std::cout << e << "\n";

    return 0;
}

