#include <cassert>
#include <vector>


template <typename Container>
void handle(Container & container, int value)
{
	container.push_back(value);
}


template <typename Container, typename T>
void handle(Container &, T)
{
}


template <typename Container, typename ... Ts>
void insert(Container & container, Ts ... args)
{
	(handle(container, args), ...);
}


int main()
{
	std::vector<int> vector;

	insert(vector, 1, 2.5, 3, 'a', 4, 5.0, 6);

	assert(vector.size() == 4);
	assert(vector[0] == 1);
	assert(vector[1] == 3);
	assert(vector[2] == 4);
	assert(vector[3] == 6);
}



