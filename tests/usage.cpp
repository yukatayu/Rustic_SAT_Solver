#include <iostream>
#include "data.hpp"
#include "solver.hpp"

int main(){
	// prepare
	/**
	 * A: mB
	 * B: mD
	 * C: !mC
	 * D: !B
	 * 
	 */
	auto clauses = ClauseSet({
		// A
		{{ "-a"_L,  "mB"_L }},
		{{ "-mB"_L,  "a"_L }},
		// B
		{{ "-b"_L, "mD"_L }},
		{{ "-mD"_L, "b"_L }},
		// C
		{{ "-c"_L, "-mC"_L }},
		{{ "mC"_L, "c"_L }},
		// D
		{{ "-d"_L, "-b"_L }},
		{{  "d"_L,  "b"_L }},
		// a + b + c + d = 1
		{{ "a"_L, "b"_L, "c"_L, "d"_L }},
		{{ "-a"_L, "-b"_L }},
		{{ "-a"_L, "-c"_L }},
		{{ "-a"_L, "-d"_L }},
		{{ "-b"_L, "-c"_L }},
		{{ "-b"_L, "-d"_L }},
		{{ "-c"_L, "-d"_L }},
		// mA + mB + mC + mD = 1
		{{ "mA"_L, "mB"_L, "mC"_L, "mD"_L }},
		{{ "-mA"_L, "-mB"_L }},
		{{ "-mA"_L, "-mC"_L }},
		{{ "-mA"_L, "-mD"_L }},
		{{ "-mB"_L, "-mC"_L }},
		{{ "-mB"_L, "-mD"_L }},
		{{ "-mC"_L, "-mD"_L }},
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
