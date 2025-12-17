//////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <numeric>

//////////////////////////////////////////////////////////////////////////////////////////

template < int N = 0, int D = 1 > struct Ratio
{
	constexpr static auto num = N;
	
	constexpr static auto den = D;
};

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 > struct Sum
{
	constexpr static auto num_raw = R1::num * R2::den + R2::num * R1::den;

	constexpr static auto den_raw = R1::den * R2::den;

	constexpr static auto gcd_val = std::gcd(num_raw, den_raw);

	constexpr static auto num = num_raw / gcd_val;

	constexpr static auto den = den_raw / gcd_val;

//  ------------------------------------------------------------------
	
	using type = Ratio < num, den > ;
};

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 > using sum = typename Sum < R1, R2 > ::type;

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 > struct Sub
{
	using type = typename Sum < R1, Ratio < -R2::num, R2::den > > ::type;
};

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 > using sub = typename Sub < R1, R2 > ::type;

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 > struct Mul
{
	constexpr static auto num_raw = R1::num * R2::num;

	constexpr static auto den_raw = R1::den * R2::den;

	constexpr static auto gcd_val = std::gcd(num_raw, den_raw);

	constexpr static auto num = num_raw / gcd_val;

	constexpr static auto den = den_raw / gcd_val;

//  ------------------------------------------------------------------
	
	using type = Ratio < num, den > ;
};

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 > using mul = typename Mul < R1, R2 > ::type;

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 > struct Div
{
	static_assert(R2::num != 0, "Division by zero");

	using type = typename Mul < R1, Ratio < R2::den, R2::num > > ::type;
};

//////////////////////////////////////////////////////////////////////////////////////////

namespace ratioOps
{
	template < typename R1, typename R2 > using div = typename Div < R1, R2 > ::type;
}

//////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename R = Ratio < 1 > > struct Duration 
{
	T x = T();

	constexpr Duration() = default;

	constexpr Duration(T const & value) : x(value) {}
};

//////////////////////////////////////////////////////////////////////////////////////////

template 
< 
	typename T1, typename R1, 
	
	typename T2, typename R2 
>
constexpr auto operator+(Duration < T1, R1 > const & lhs, Duration < T2, R2 > const & rhs)
{
	using ratio_t = Ratio < 1, sum < R1, R2 > ::den > ;

	auto x = 
	(
		lhs.x * ratio_t::den / R1::den * R1::num +

		rhs.x * ratio_t::den / R2::den * R2::num
	);

	return Duration < decltype(x), ratio_t > (x);
}

//////////////////////////////////////////////////////////////////////////////////////////

template 
< 
	typename T1, typename R1, 
	
	typename T2, typename R2 
>
constexpr auto operator-(Duration < T1, R1 > const & lhs, Duration < T2, R2 > const & rhs)
{
	return lhs + Duration < T2, R2 > (-rhs.x);
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	using ratioOps::div;

	auto x = 1, y = 2;

//  ----------------------------------------------------------------------

	Duration < int, Ratio < 1, 2 > > duration_1(x);

	Duration < int, Ratio < 1, 3 > > duration_2(y);

//  ----------------------------------------------------------------------

	Duration < int, Ratio < 1, 6 > > duration_3 = duration_1 + duration_2;

//  ----------------------------------------------------------------------

	assert(duration_3.x == 7);

//  ----------------------------------------------------------------------

	static_assert(Sum < Ratio < 1, 2 >, Ratio < 1, 3 > > ::num == 5);
	static_assert(Sum < Ratio < 1, 2 >, Ratio < 1, 3 > > ::den == 6);

	static_assert(Sub < Ratio < 1, 2 >, Ratio < 1, 3 > > ::type::num == 1);
	static_assert(Sub < Ratio < 1, 2 >, Ratio < 1, 3 > > ::type::den == 6);

	static_assert(Mul < Ratio < 1, 2 >, Ratio < 1, 3 > > ::num == 1);
	static_assert(Mul < Ratio < 1, 2 >, Ratio < 1, 3 > > ::den == 6);

	static_assert(Div < Ratio < 1, 2 >, Ratio < 1, 3 > > ::type::num == 3);
	static_assert(Div < Ratio < 1, 2 >, Ratio < 1, 3 > > ::type::den == 2);

}

//////////////////////////////////////////////////////////////////////////////////////////