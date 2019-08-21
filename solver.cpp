#include "data.hpp"
#include "solver.hpp"

using res_type = std::tuple<bool, std::vector<std::map<Proposition, bool>>>;

res_type solve(ClauseSet clauses){
	// unit rule
	for(;;){
		if(auto maybePrimeLiteral = clauses.getPrimeLiteral()){
				auto primeLiteral = maybePrimeLiteral.value();
				clauses.determine(primeLiteral.prop, !primeLiteral.invert);
				clauses.removeClausesWhichHas(primeLiteral);
				primeLiteral.invert = !primeLiteral.invert;
				clauses.removeAll(primeLiteral);
		} else break;
	}
	// exit
	if(clauses.isSatisfiable())
		return res_type{true, {clauses.determined}};
	if(clauses.isContradicted())
		return res_type{false, {}};
	// recursion
	Proposition splitProp = *clauses.getOneProposition();
	auto clauses2 = clauses;
		// recursion 1
		clauses.clauses.push_back(Clause{{Literal{splitProp, false}}});
		auto [satisfiable_true, conds_true] = solve(clauses);
		// recursion 2
		clauses2.clauses.push_back(Clause{{Literal{splitProp, true}}});
		auto [satisfiable_false, conds_false] = solve(clauses2);
		// merge
		if(satisfiable_true || satisfiable_false){
			std::copy(conds_false.begin(), conds_false.end(), std::back_inserter(conds_true));
			return res_type{true, conds_true};
		}
	// end
	return res_type{false, {}};
}
