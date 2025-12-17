#include <iostream>
#include <cmath>
#include <optional>
#include <variant>
#include <utility>

constexpr double eps = 1e-12;

using Roots = std::variant<double, std::pair<double, double>, std::monostate>;

std::optional<Roots> solve(double a, double b, double c)
{
    if (std::abs(a) < eps)
    {
        if (std::abs(b) < eps)
        {
            if (std::abs(c) < eps)
            {
                return std::make_optional<Roots>(std::monostate{});
            }
            else
            {
                return std::nullopt;
            }
        }
        else
        {
            double x = -c / b;
            return std::make_optional<Roots>(x);
        }
    }
    else
    {
        double d = b * b - 4 * a * c;
        if (std::abs(d) < eps)
        {
            double x = -b / (2 * a);
            return std::make_optional<Roots>(x);
        }
        else if (d < 0)
        {
            return std::nullopt;
        }
        else
        {
            double x1 = (-b + std::sqrt(d)) / (2 * a);
            double x2 = (-b - std::sqrt(d)) / (2 * a);
            return std::make_optional<Roots>(std::make_pair(x1, x2));
        }
    }
}

int main()
{
    double a, b, c;
    std::cin >> a >> b >> c;

    auto result = solve(a, b, c);

    if (!result.has_value())
    {
        std::cout << "No solution\n";
    }
    else
    {
        const auto& roots = result.value();
        if (std::holds_alternative<std::monostate>(roots))
        {
            std::cout << "X can be any real number\n";
        }
        else if (std::holds_alternative<double>(roots))
        {
            double x = std::get<double>(roots);
            std::cout << "X = " << x << "\n";
        }
        else if (std::holds_alternative<std::pair<double, double>>(roots))
        {
            const auto& pair = std::get<std::pair<double, double>>(roots);
            std::cout << "X1 = " << pair.first << "\n";
            std::cout << "X2 = " << pair.second << "\n";
        }
    }

    return 0;
}

