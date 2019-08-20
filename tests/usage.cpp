#include <iostream>
#include "data.hpp"
#include "solver.hpp"

int main(){
	auto clauses = ClauseSet({
		{{ Literal{"a", true}, Literal{"b", true}, Literal{"c", true}}},
		{{ Literal{"a", false}, Literal{"b", true}, Literal{"c", true}}},
		{{ Literal{"b", false}}},
	});
	bool isSAT;
	std::vector<ClauseSet> conds;
	std::tie(isSAT, conds) = solve(clauses);
	std::cout << (isSAT ? "This is SAT" : "This is not SAT") << std::endl;
	for(auto&& cond : conds){
		std::cout << "----------" << std::endl;
		for(auto&& kv : cond.defined)
			std::cout << kv.first.name << " = " << kv.second << std::endl;
	}
}

