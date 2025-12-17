#include <algorithm>
#include <cassert>




double maximum(double x)
{
	return x;
}


template < typename ... Ts >
double maximum(double x, Ts ... xs)
{
	return std::max(x, maximum(xs...));
}


double minimum(double x)
{
	return x;
}


template < typename ... Ts >
double minimum(double x, Ts ... xs)
{
	return std::min(x, minimum(xs...));
}


template <typename ... Ts>
double sum(Ts ... xs)
{
	return (... + xs);
}


template < typename ... Ts >
double mean( Ts ... xs)
{
	return (... + xs) / (sizeof...(xs) + 1);
}


int main()
{
	assert(maximum(1.0, 2.0, 3.0) == 3.0);

	assert(minimum(5.0, 2.0, 8.0, 1.0) == 1.0);

	assert(sum(5.0, 2.0, 8.0, 1.0) == 16.0);

	assert(mean(5.0, 2.0, 8.0, 1.0) == 4.0);
}



