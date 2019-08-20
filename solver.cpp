#include "data.hpp"
#include "solver.hpp"

using res_type = std::tuple<bool, std::vector<ClauseSet>>;

res_type solve(ClauseSet clauses){
	// unit rule
	for(;;){
		bool found = false;
		for(auto&& clause : clauses.clauses){
			if(clause.isPrime()){
				found = true;
				auto primeLiteral = *clause.literals.begin();  // must copy
				clauses.define(primeLiteral.prop, !primeLiteral.invert);
				clauses.removeClausesWhichHas(primeLiteral);
				primeLiteral.invert = !primeLiteral.invert;
				clauses.removeAll(primeLiteral);
			}
		}
		if(!found)
			break;
	}
	// exit
	if(clauses.isSatisfiable())
		return res_type{true, {clauses}};
	if(clauses.isContradicted())
		return res_type{false, {}};
	// recursion
	bool satisfiable[2];
	std::vector<ClauseSet> conds[2];
	Proposition splitProp = clauses.getOneProposition();
	auto clauses2 = clauses;
		// recursion 1
		clauses.clauses.push_back(Clause{{Literal{splitProp, false}}});
		std::tie(satisfiable[0], conds[0]) = solve(clauses);
		// recursion 2
		clauses2.clauses.push_back(Clause{{Literal{splitProp, true}}});
		std::tie(satisfiable[1], conds[1]) = solve(clauses2);
		// merge
		if(satisfiable[0] || satisfiable[1]){
			std::copy(conds[1].begin(),conds[1].end(),std::back_inserter(conds[0]));
			return res_type{satisfiable, conds[0]};
		}
	// end
	return res_type{false, {}};
}
