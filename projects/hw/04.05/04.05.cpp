#include <limits>



template<int N> struct Fibonacci
{
	static_assert(Fibonacci<N - 1>::value <= std::numeric_limits<int>::max() - Fibonacci<N - 2>::value, "Overflow!");

	static const int value = Fibonacci<N - 1>::value + Fibonacci< N - 2 >::value;
};


template<> struct Fibonacci<0>
{
	static const int value = 0;
};


template<> struct Fibonacci<1>
{
	static const int value = 1;
};


template<int N> const int fibonacci_v = Fibonacci<N>::value;


int main()
{
	static_assert(fibonacci_v<0> == 0);
	static_assert(fibonacci_v<1> == 1);
	static_assert(fibonacci_v<2> == 1);
	static_assert(fibonacci_v<3> == 2);
	static_assert(fibonacci_v<7> == 13);
	static_assert(fibonacci_v<10> == 55);
}



