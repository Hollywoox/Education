////////////////////////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/ComparisonSort.html

////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>
#include <ranges>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

namespace custom {

template <typename It>
void order(It first, It last)
{
	for (auto i = std::next(first); i != last; ++i)
	{
		for (auto j = i; j != first; --j)
		{
			auto prev_j = std::prev(j);
			if (*prev_j > *j)
			{
				std::iter_swap(j, prev_j);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////

template <typename It>
void choose_pivot(It first, It last)
{
	auto dist = std::distance(first, last);
	auto middle = std::next(first, (dist - 1) / 2);
	auto last_it = std::prev(last);

	auto first_val = *first;
	auto middle_val = *middle;
	auto last_val = *last_it;

	if ((first_val <= middle_val && middle_val <= last_val) ||
	    (last_val <= middle_val && middle_val <= first_val))
	{
		std::iter_swap(first, middle);
	}
	else if ((middle_val <= last_val && last_val <= first_val) ||
	         (first_val <= last_val && last_val <= middle_val))
	{
		std::iter_swap(first, last_it);
	}
}

////////////////////////////////////////////////////////////////////////////////////

template <typename It>
It partition(It first, It last)
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
		while (i != last && *i < pivot);

		do
		{
			std::advance(j, -1);
		}
		while (j != first && *j > pivot);

		if (std::distance(first, i) >= std::distance(first, j))
		{
			break;
		}

		std::iter_swap(i, j);
	}

	std::iter_swap(first, j);

	return j;
}

////////////////////////////////////////////////////////////////////////////////////

template <typename It>
void split(It first, It last)
{
	if (std::distance(first, last) > 16)
	{
		choose_pivot(first, last);

		auto pivot_pos = partition(first, last);

		split(first, pivot_pos);
		split(std::next(pivot_pos), last);
	}
	else
	{
		order(first, last);
	}
}

////////////////////////////////////////////////////////////////////////////////////

template <typename It>
void sort(It first, It last)
{
	if (first != last)
	{
		split(first, last);
	}
}

} // namespace custom

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 1'000uz;

//  ---------------------------------------

	std::vector<int> vector(size, 0);

//  ---------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		vector[i] = size - i;
	}

//  ---------------------------------------

	custom::sort(vector.begin(), vector.end());

//  ---------------------------------------

	assert(std::is_sorted(vector.begin(), vector.end()));
}

////////////////////////////////////////////////////////////////////////////////////
