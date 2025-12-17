#include <iostream>
#include <cmath>
#include <array>
#include <limits>


constexpr double absConstexpr(double x)
{
    return x < 0.0 ? -x : x;
}

consteval double compute_pi(double epsilon)
{
    double pi = 0.0;
    int n = 0;
    double term = 1.0;
    
    while (absConstexpr(term) >= epsilon)
    {
        pi += term;
        n++;
        term = (n % 2 == 0 ? 1.0 : -1.0) / (2.0 * n + 1.0);
    }
    return pi * 4.0;
}


consteval double compute_e(double epsilon)
{
    double e = 0.0;
    int n = 0;
    double term = 1.0;
    
    while (absConstexpr(term) >= epsilon)
    {
        e += term;
        n++;
        term = term / static_cast<double>(n);
    }
    return e;
}

int main()
{
    constexpr std::array<double, 2> epsilons = {1e-2, 1e-4};

    constexpr std::array<double, 2> pi_values = {compute_pi(epsilons[0]), compute_pi(epsilons[1])};

    constexpr std::array<double, 2> e_values = {compute_e(epsilons[0]), compute_e(epsilons[1])};


    static_assert(pi_values[0] > 3.0 && pi_values[0] < 3.3, "Pi calculation error for epsilon=1e-2");
    static_assert(pi_values[1] > 3.14 && pi_values[1] < 3.142, "Pi calculation error for epsilon=1e-4");

    static_assert(e_values[0] > 2.7 && e_values[0] < 2.72, "E calculation error for epsilon=1e-2");
    static_assert(e_values[1] > 2.7182 && e_values[1] < 2.7183, "E calculation error for epsilon=1e-4");

    for (std::size_t i = 0; i < epsilons.size(); ++i)
    {
        std::cout << "epsilon = " << epsilons[i] << ":\n";
        std::cout << "pi = " << pi_values[i] << "\n";
        std::cout << "e = " << e_values[i] << "\n";
    }

    return 0;
}

