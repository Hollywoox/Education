export module rational:helpers;

namespace rational_ns {

template<typename Derived>
export class addable
{
public:
	friend auto operator+(Derived lhs, Derived const & rhs)
	{
		return lhs += rhs;
	}
};

template<typename Derived>
export class subtractable
{
public:
	friend auto operator-(Derived lhs, Derived const & rhs)
	{
		return lhs -= rhs;
	}
};

template<typename Derived>
export class multipliable
{
public:
	friend auto operator*(Derived lhs, Derived const & rhs)
	{
		return lhs *= rhs;
	}
};

template<typename Derived>
export class dividable
{
public:
	friend auto operator/(Derived lhs, Derived const & rhs)
	{
		return lhs /= rhs;
	}
};

template<typename Derived>
export class incrementable
{
public:
	friend auto operator++(Derived & derived, int)
	{
		auto x = derived;
		++derived;
		return x;
	}
};

template<typename Derived>
export class decrementable
{
public:
	friend auto operator--(Derived & derived, int)
	{
		auto x = derived;
		--derived;
		return x;
	}
};

} // namespace rational_ns

