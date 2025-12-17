import rational;

import <cassert>;
import <cmath>;
import <sstream>;
import <vector>;

using namespace rational_ns;

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

int main()
{
	Rational<int> x = 1, y(2, 1);

	// -----------------------------------------------------------------------

	// std::vector<int> vector_1 = 5; // error

	std::vector<int> vector_2(5);

	std::vector<int> vector_3 = { 1, 2, 3, 4, 5 };

	// -----------------------------------------------------------------------

	assert(equal(static_cast<double>(x), 1));

	// -----------------------------------------------------------------------

	// assert(x.operator+=(y) == Rational(3, 1)); // bad

	// -----------------------------------------------------------------------

	assert((x += y) == Rational<int>(+3, 1));

	assert((x -= y) == Rational<int>(+1, 1));

	assert((x *= y) == Rational<int>(+2, 1));

	assert((x /= y) == Rational<int>(+1, 1));

	// -----------------------------------------------------------------------

	assert((x++) == Rational<int>(+1, 1)); // support : compiler-explorer.com

	assert((x--) == Rational<int>(+2, 1));

	assert((++y) == Rational<int>(+3, 1)); // support : compiler-explorer.com

	assert((--y) == Rational<int>(+2, 1));

	// -----------------------------------------------------------------------

	// x++++; // error

	// -----------------------------------------------------------------------

	[[maybe_unused]] auto z = 0;

	// -----------------------------------------------------------------------

	// z++++; // error

	// -----------------------------------------------------------------------

	// assert(operator+(x, y) == Rational(3, 1)); // bad

	// -----------------------------------------------------------------------

	assert((x + y) == Rational<int>(+3, 1));

	assert((x - y) == Rational<int>(-1, 1));

	assert((x * y) == Rational<int>(+2, 1));

	assert((x / y) == Rational<int>(+1, 2));

	// -----------------------------------------------------------------------

	assert((x += 1) == Rational<int>(+2, 1));

	// assert((1 += x) == Rational(+3, 1)); // error

	assert((x + 1) == Rational<int>(+3, 1));

	assert((1 + y) == Rational<int>(+3, 1));

	assert((1 + 1) == Rational<int>(+2, 1));

	// -----------------------------------------------------------------------

	assert((x < y) == 0);
	
	assert((x > y) == 0);

	assert((x <= y) == 1);

	assert((x >= y) == 1);

	assert((x == y) == 1);

	assert((x != y) == 0);

	// -----------------------------------------------------------------------

	std::stringstream stream_1("1/2");

	std::stringstream stream_2;
	
	// -----------------------------------------------------------------------

	stream_1 >> x;

	stream_2 << x;

	// -----------------------------------------------------------------------

	assert(stream_2.str() == stream_1.str());
}

