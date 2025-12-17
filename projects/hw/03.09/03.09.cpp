#include <cstdint>
#include <iostream>

class IPv4
{
public:

	IPv4() : m_address{0, 0, 0, 0}
	{
	}

	IPv4(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d)
		: m_address{a, b, c, d}
	{
	}

	IPv4 & operator++()
	{
		for (int i = 3; i >= 0; --i)
		{
			if (m_address[i] < 255)
			{
				++m_address[i];
				break;
			}
			else
			{
				m_address[i] = 0;
			}
		}
		return *this;
	}


	IPv4 operator++(int)
	{
		IPv4 temp = *this;
		++(*this);
		return temp;
	}


	IPv4 & operator--()
	{
		for (int i = 3; i >= 0; --i)
		{
			if (m_address[i] > 0)
			{
				--m_address[i];
				break;
			}
			else
			{
				m_address[i] = 255;
			}
		}
		return *this;
	}


	IPv4 operator--(int)
	{
		IPv4 temp = *this;
		--(*this);
		return temp;
	}


	friend bool operator==(IPv4 const & lhs, IPv4 const & rhs)
	{
		return lhs.m_address[0] == rhs.m_address[0] &&
		       lhs.m_address[1] == rhs.m_address[1] &&
		       lhs.m_address[2] == rhs.m_address[2] &&
		       lhs.m_address[3] == rhs.m_address[3];
	}


	friend bool operator!=(IPv4 const & lhs, IPv4 const & rhs)
	{
		return !(lhs == rhs);
	}


	friend bool operator<(IPv4 const & lhs, IPv4 const & rhs)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (lhs.m_address[i] < rhs.m_address[i])
				return true;
			if (lhs.m_address[i] > rhs.m_address[i])
				return false;
		}
		return false;
	}


	friend bool operator>(IPv4 const & lhs, IPv4 const & rhs)
	{
		return rhs < lhs;
	}


	friend bool operator<=(IPv4 const & lhs, IPv4 const & rhs)
	{
		return !(lhs > rhs);
	}


	friend bool operator>=(IPv4 const & lhs, IPv4 const & rhs)
	{
		return !(lhs < rhs);
	}


	friend std::istream & operator>>(std::istream & is, IPv4 & ip)
	{
		int a, b, c, d;
		char dot1, dot2, dot3;

		if (is >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d)
		{
			if (dot1 == '.' && dot2 == '.' && dot3 == '.' &&
			    a >= 0 && a <= 255 &&
			    b >= 0 && b <= 255 &&
			    c >= 0 && c <= 255 &&
			    d >= 0 && d <= 255)
			{
				ip.m_address[0] = static_cast<std::uint8_t>(a);
				ip.m_address[1] = static_cast<std::uint8_t>(b);
				ip.m_address[2] = static_cast<std::uint8_t>(c);
				ip.m_address[3] = static_cast<std::uint8_t>(d);
			}
			else
			{
				is.setstate(std::ios::failbit);
			}
		}

		return is;
	}



	friend std::ostream & operator<<(std::ostream & os, IPv4 const & ip)
	{
		os << static_cast<int>(ip.m_address[0]) << '.'
		   << static_cast<int>(ip.m_address[1]) << '.'
		   << static_cast<int>(ip.m_address[2]) << '.'
		   << static_cast<int>(ip.m_address[3]);
		return os;
	}

private:

	std::uint8_t m_address[4];
};


int main()
{
	IPv4 ip1;
	IPv4 ip2(192, 168, 32, 8);

	std::cout << "ip1: " << ip1 << "\n";
	std::cout << "ip2: " << ip2 << "\n";

	std::cout << "\nEnter IP address: ";
	std::cin >> ip1;
	std::cout << "You entered: " << ip1 << "\n";

	std::cout << "\nTesting increment:\n";
	std::cout << "ip2: " << ip2 << "\n";
	std::cout << "++ip2: " << ++ip2 << "\n";
	std::cout << "ip2++: " << ip2++ << "\n";
	std::cout << "ip2: " << ip2 << "\n";

	std::cout << "\nTesting decrement:\n";
	std::cout << "ip2: " << ip2 << "\n";
	std::cout << "--ip2: " << --ip2 << "\n";
	std::cout << "ip2--: " << ip2-- << "\n";
	std::cout << "ip2: " << ip2 << "\n";

	std::cout << "\nTesting comparison:\n";
	IPv4 ip3(192, 168, 1, 1);
	IPv4 ip4(192, 168, 1, 2);
	std::cout << "ip3: " << ip3 << "\n";
	std::cout << "ip4: " << ip4 << "\n";
	std::cout << "ip3 == ip4: " << (ip3 == ip4) << "\n";
	std::cout << "ip3 != ip4: " << (ip3 != ip4) << "\n";
	std::cout << "ip3 < ip4: " << (ip3 < ip4) << "\n";
	std::cout << "ip3 > ip4: " << (ip3 > ip4) << "\n";
	std::cout << "ip3 <= ip4: " << (ip3 <= ip4) << "\n";
	std::cout << "ip3 >= ip4: " << (ip3 >= ip4) << "\n";

	return 0;
}


