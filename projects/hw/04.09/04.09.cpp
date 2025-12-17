#include <type_traits>


template < typename T > 
class is_class
{
private:
	template < typename U >
	static char test(int U::*);

	template < typename U >
	static long test(...);

public :

	static constexpr bool value = sizeof(test<T>(nullptr)) == sizeof(char);
};

template < typename T >
inline constexpr bool is_class_v = is_class<T>::value;


template < typename T >
struct add_const
{
	using type = const T;
};

template < typename T >
struct add_const<T &>
{
	using type = T &;
};

template < typename T >
struct add_const<T &&>
{
	using type = T &&;
};

template < typename T >
using add_const_t = typename add_const<T>::type;

template < typename T >
struct remove_const
{
	using type = T;
};

template < typename T >
struct remove_const<const T>
{
	using type = T;
};

template < typename T >
using remove_const_t = typename remove_const<T>::type;


template < bool B, typename T, typename F >
struct conditional
{
	using type = T;
};

template < typename T, typename F >
struct conditional<false, T, F>
{
	using type = F;
};

template < bool B, typename T, typename F >
using conditional_t = typename conditional<B, T, F>::type;


template < typename T >
struct decay
{
private :

	using U = typename std::remove_reference<T>::type;

public :

	using type =
		std::conditional_t
		<
			std::is_array<U>::value,
			typename std::remove_extent<U>::type *,
			std::conditional_t
			<
				std::is_function<U>::value,
				typename std::add_pointer<U>::type,
				typename std::remove_cv<U>::type
			>
		>;
};

template < typename T >
using decay_t = typename decay<T>::type;


struct TestClass {};

union TestUnion
{
	int x;
};

enum class TestEnum : int {};

int test_function(double, char);


int main()
{
	static_assert(is_class<TestClass>::value);
	static_assert(is_class_v<TestClass>);
	static_assert(!is_class<int>::value);
	static_assert(!is_class_v<TestEnum>);

	static_assert(std::is_same_v<add_const_t<int>, const int>);
	static_assert(std::is_same_v<add_const_t<const int>, const int>);
	static_assert(std::is_same_v<add_const_t<int &>, int &>);
	static_assert(std::is_same_v<add_const_t<int &&>, int &&>);

	static_assert(std::is_same_v<remove_const_t<const int>, int>);
	static_assert(std::is_same_v<remove_const_t<int>, int>);

	static_assert(std::is_same_v<conditional_t<true, int, double>, int>);
	static_assert(std::is_same_v<conditional_t<false, int, double>, double>);

	static_assert(std::is_same_v<decay_t<const int>, int>);
	static_assert(std::is_same_v<decay_t<int &>, int>);
	static_assert(std::is_same_v<decay_t<int &&>, int>);

	static_assert(std::is_same_v<decay_t<int[5]>, int *>);
	static_assert(std::is_same_v<decay_t<const int[5]>, const int *>);

	static_assert(std::is_same_v<decay_t<int(double, char)>, int (*)(double, char)>);

	return 0;
}


