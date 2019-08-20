#include <iostream>
#include "data.hpp"
#include "solver.hpp"

int main(){
	// prepare
	auto clauses = ClauseSet({
		{{ Literal{"a", true}, Literal{"b", true}, Literal{"c", true}}},
		{{ Literal{"a", false}, Literal{"b", true}, Literal{"c", true}}},
		{{ Literal{"b", false}}},
	});
	// solve
	auto [isSAT, conds] = solve(clauses);
	// print
	std::cout << (isSAT ? "This is SAT" : "This is not SAT") << std::endl;
	for(auto&& cond : conds){
		std::cout << "----------" << std::endl;
		for(auto&& kv : cond.defined)
			std::cout << kv.first.name << " = " << kv.second << std::endl;
	}
}

