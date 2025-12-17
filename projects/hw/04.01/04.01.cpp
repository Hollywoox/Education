////////////////////////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/ComparisonSort.html

////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <ranges>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

template < typename T >
void order(std::vector<T> & vector, std::size_t left, std::size_t right)
{
	for (auto i = left + 1; i < right; ++i) 
	{
		for (auto j = i; j > left; --j)
		{
			if (vector[j - 1] > vector[j]) 
			{
				std::swap(vector[j], vector[j - 1]);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void choose_pivot(std::vector<T> & vector, std::size_t left, std::size_t right)
{
	auto middle = left + (right - 1 - left) / 2;
	auto last = right - 1;

	auto first_val = vector[left];
	auto middle_val = vector[middle];
	auto last_val = vector[last];

	if ((first_val <= middle_val && middle_val <= last_val) ||
	    (last_val <= middle_val && middle_val <= first_val))
	{
		std::swap(vector[left], vector[middle]);
	}
	else if ((middle_val <= last_val && last_val <= first_val) ||
	         (first_val <= last_val && last_val <= middle_val))
	{
		std::swap(vector[left], vector[last]);
	}
}

////////////////////////////////////////////////////////////////////////////////////

template<typename T >
std::size_t partition(std::vector<T> & vector, std::size_t left, std::size_t right)
{
	auto pivot = vector[left];
	auto i = left;
	auto j = right;

	while (true)
	{
		do
		{
			++i;
		}
		while (i < right && vector[i] < pivot);

		do
		{
			--j;
		}
		while (j > left && vector[j] > pivot);

		if (i >= j)
		{
			break;
		}

		std::swap(vector[i], vector[j]);
	}

	std::swap(vector[left], vector[j]);

	return j;
}

////////////////////////////////////////////////////////////////////////////////////

template<typename T>
void split(std::vector<T> & vector, std::size_t left, std::size_t right)
{
	if (right - left > 16)
	{
		choose_pivot(vector, left, right);

		auto pivot_pos = partition(vector, left, right);

		split(vector, left, pivot_pos);
		split(vector, pivot_pos + 1, right);
	}
	else
	{
		order(vector, left, right);
	}
}


template<typename T>
void sort(std::vector<T> & vector)
{
	split(vector, 0, std::size(vector));
}

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

	sort(vector);

//  ---------------------------------------

	assert(std::is_sorted(vector.begin(), vector.end()));
}

////////////////////////////////////////////////////////////////////////////////////