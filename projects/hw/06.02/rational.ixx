export module rational;


import :helpers;

import <compare>;
import <istream>;
import <numeric>;
import <ostream>;

namespace rational_ns {

template<typename T>
class Rational : public addable<Rational<T>>,
                 public subtractable<Rational<T>>,
                 public multipliable<Rational<T>>,
                 public dividable<Rational<T>>,
                 public incrementable<Rational<T>>,
                 public decrementable<Rational<T>>
{
public:
	Rational(T num = 0, T den = 1);

	explicit operator double() const
	{ 
		return 1.0 * m_num / m_den;
	}

	Rational & operator+=(Rational const & other);
	Rational & operator-=(Rational const & other) 
	{ 
		return *this += Rational(other.m_num * -1, other.m_den);
	}
	Rational & operator*=(Rational const & other);
	Rational & operator/=(Rational const & other) 
	{ 
		return *this *= Rational(other.m_den, other.m_num);
	}

	Rational & operator++() { *this += 1; return *this; }
	Rational & operator--() { *this -= 1; return *this; }

	friend std::strong_ordering operator<=>(Rational const & lhs, Rational const & rhs)
	{
		auto lhs_value = static_cast<long long>(lhs.m_num) * rhs.m_den;
		auto rhs_value = static_cast<long long>(rhs.m_num) * lhs.m_den;

		if (lhs_value < rhs_value)
		{
			return std::strong_ordering::less;
		}
		else if (lhs_value > rhs_value)
		{
			return std::strong_ordering::greater;
		}
		else
		{
			return std::strong_ordering::equal;
		}
	}

	friend auto operator==(Rational const & lhs, Rational const & rhs)
	{
		return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
	}

	friend auto & operator>>(std::istream & stream, Rational & rational)
	{
		return (stream >> rational.m_num).ignore() >> rational.m_den;
	}

	friend auto & operator<<(std::ostream & stream, Rational const & rational)
	{
		return stream << rational.m_num << '/' << rational.m_den;
	}

private:
	void reduce();
	T m_num = 0, m_den = 1;
};

} // namespace rational_ns


export namespace rational_ns {
	using rational_ns::Rational;
}

