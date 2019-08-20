#include <iostream>
#include "data.hpp"
#include "solver.hpp"

int main(){
	auto a = solve(EmptyData());
	std::cout << "OK" << std::endl;
}

