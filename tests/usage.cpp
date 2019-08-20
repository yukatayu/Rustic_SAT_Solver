#include <iostream>
#include "data.hpp"
#include "solver.hpp"

int main(){
	// prepare
	/**
	 * A: !B && !C
	 * B: !A
	 * C: !B
	 */
	/**
	 * (!A || !B) && (!A || !C) && (B || C || A)
	 * (!A || !B) && (B || A)
	 * (!B || !C) && (C || B)
	 */
	auto clauses = ClauseSet({
		// A
		{{ "-a"_L, "-b"_L }},
		{{ "-a"_L, "-c"_L }},
		{{  "b"_L,  "c"_L,  "a"_L }},
		// B
		{{ "-a"_L, "-b"_L }},
		{{  "b"_L,  "a"_L }},
		// C
		{{ "-b"_L, "-c"_L }},
		{{  "c"_L,  "b"_L }}
	});
	// solve
	auto [isSAT, conds] = solve(clauses);
	// print
	std::cout << (isSAT ? "This is SAT" : "This is not SAT") << std::endl;
	for(auto&& cond : conds){
		std::cout << "----------" << std::endl;
		for(auto&& kv : cond)
			std::cout << kv.first.name << " = " << kv.second << std::endl;
	}
}
