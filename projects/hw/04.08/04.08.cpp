//////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>

//////////////////////////////////////////////////////////////////

template < typename ... Ts > class Tuple 
{
public :
	constexpr std::size_t size() const { return sizeof...(Ts); }
};

//////////////////////////////////////////////////////////////////

template<typename T, typename ... Ts> class Tuple<T, Ts ... >
{
public :

	constexpr Tuple(T && x, Ts && ... xs)
	:
		m_head(std::forward < T  > (x )   ),
		
		m_tail(std::forward < Ts > (xs)...)
	{}

//  ------------------------------------------------

	template<std::size_t i> constexpr auto get() const
	{
		if constexpr (i > 0)
		{
			return m_tail.template get<i - 1> ();
		}
		else
		{
			return m_head;
		}
	}

//  ------------------------------------------------

	constexpr std::size_t size() const { return 1 + sizeof...(Ts); }

private :

	T m_head;
	
	Tuple < Ts ... > m_tail;
};

//////////////////////////////////////////////////////////////////

int main()
{
	Tuple<int, double, std::string > tuple(1, 2.0, "aaaaa");



	assert(tuple.get<0>() == 1);


	constexpr Tuple<int, double, char > constexpr_tuple(1, 2.0, 'z');
	
	static_assert(constexpr_tuple.size() == 3);
	static_assert(constexpr_tuple.get<0>() == 1);
	static_assert(constexpr_tuple.get<1>() == 2.0);
	static_assert(constexpr_tuple.get<2>() == 'z');
	
	constexpr Tuple<int> single_tuple(42);
	static_assert(single_tuple.size() == 1);
	static_assert(single_tuple.get<0>() == 42);
	
	constexpr Tuple<> empty_tuple;
	static_assert(empty_tuple.size() == 0);
}

//////////////////////////////////////////////////////////////////