#include <iostream>
#include "data.hpp"
#include "solver.hpp"

int main(){
	auto clauses = ClauseSet({
		{{ Literal{"a", true}, Literal{"b", true}, Literal{"c", true}}},
		{{ Literal{"a", false}, Literal{"b", true}, Literal{"c", true}}},
		{{ Literal{"b", false}}},
	});
	std::cout << "OK" << std::endl;
}

