////////////////////////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/ComparisonSort.html

////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <iterator>
#include <numeric>
#include <ranges>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

namespace custom {

template <typename It, typename Comp>
void order(It first, It last, Comp comp)
{
	for (auto i = std::next(first); i != last; ++i)
	{
		for (auto j = i; j != first; --j)
		{
			auto prev_j = std::prev(j);
			if (comp(*j, *prev_j))
			{
				std::iter_swap(j, prev_j);
			}
		}
	}
}


template <typename It, typename Comp>
void choose_pivot(It first, It last, Comp comp)
{
	auto dist = std::distance(first, last);
	auto middle = std::next(first, (dist - 1) / 2);
	auto last_it = std::prev(last);

	auto first_val = *first;
	auto middle_val = *middle;
	auto last_val = *last_it;

	if ((!comp(middle_val, first_val) && !comp(last_val, middle_val)) ||
	    (!comp(middle_val, last_val) && !comp(first_val, middle_val)))
	{
		std::iter_swap(first, middle);
	}
	else if ((!comp(last_val, middle_val) && !comp(first_val, last_val)) ||
	         (!comp(last_val, first_val) && !comp(middle_val, last_val)))
	{
		std::iter_swap(first, last_it);
	}
}


template <typename It, typename Comp>
It partition(It first, It last, Comp comp)
{
	auto pivot = *first;
	auto i = first;
	auto j = last;

	while (true)
	{
		do
		{
			std::advance(i, 1);
		}
		while (i != last && comp(*i, pivot));

		do
		{
			std::advance(j, -1);
		}
		while (j != first && comp(pivot, *j));

		if (std::distance(first, i) >= std::distance(first, j))
		{
			break;
		}

		std::iter_swap(i, j);
	}

	std::iter_swap(first, j);

	return j;
}


template <typename It, typename Comp>
void split(It first, It last, Comp comp)
{
	if (std::distance(first, last) > 16)
	{
		choose_pivot(first, last, comp);

		auto pivot_pos = custom::partition(first, last, comp);

		split(first, pivot_pos, comp);
		split(std::next(pivot_pos), last, comp);
	}
	else
	{
		order(first, last, comp);
	}
}


template <typename It, typename Comp = std::less<>>
void sort(It first, It last, Comp comp = {})
{
	if (first != last)
	{
		split(first, last, comp);
	}
}

} // namespace custom



bool greater(int a, int b)
{
	return a > b;
}


static std::vector<int> make_reversed_vector(std::size_t size)
{
	std::vector<int> v(size, 0);
	for (std::size_t i = 0; i < size; ++i)
	{
		v[i] = static_cast<int>(size - i);
	}
	return v;
}


TEST(SortTest, FreeFunction)
{
	auto v = make_reversed_vector(1000);
	custom::sort(v.begin(), v.end(), greater);
	EXPECT_TRUE(std::is_sorted(v.begin(), v.end(), greater));
}

TEST(SortTest, StdLess)
{
	auto v = make_reversed_vector(1000);
	custom::sort(v.begin(), v.end(), std::less<int>{});
	EXPECT_TRUE(std::is_sorted(v.begin(), v.end(), std::less<int>{}));
}

TEST(SortTest, Lambda)
{
	auto v = make_reversed_vector(1000);
	custom::sort(v.begin(), v.end(), [](int a, int b) { return a < b; });
	EXPECT_TRUE(std::is_sorted(v.begin(), v.end(), [](int a, int b) { return a < b; }));
}

////////////////////////////////////////////////////////////////////////////////////
