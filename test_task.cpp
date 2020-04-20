#include <iostream>
#include "Matrix.h"
#include"Version1.h"

int main()
{
	Matrix<int> test(3);
	std::ifstream in("in.txt");
	if (in.is_open()) {
		test.input(in);
	}
	else {
		std::cout << "Error input!!!" << std::endl;
	}
	Version1 ss(test, 1, 1);
	ss.get_data().output(std::cout);
	ss.get_map_visibility().output(std::cout);

	return 1;
}
