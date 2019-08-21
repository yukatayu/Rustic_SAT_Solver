#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <exception>
#include <optional>

struct Proposition {
    std::string name;
    bool operator<(const Proposition& other) const {
        return name < other.name;
    }
    bool operator==(const Proposition& other) const {
        return name == other.name;
    }
};

struct Literal {
    Proposition prop;
    bool invert = false;
    bool operator<(const Literal& other) const {
        if(!(prop == other.prop))
            return prop < other.prop;
        return invert < other.invert;
    }
    bool operator==(const Literal& other) const {
        return prop == other.prop && invert == other.invert;
    }
};

inline Literal operator"" _L(const char* name, std::size_t length){
    Literal lit{name, false};
    if(name[0] == '-'){
        lit.prop.name = name + 1;
        lit.invert = true;
    }
    return lit;
}

struct Clause {
    std::set<Literal> literals;
    bool has(const Literal& lit) const { return literals.count(lit); }
    bool isContradicted() const { return literals.empty(); }
    bool isPrime() const { return literals.size() == 1; }
    void remove(const Literal& lit){ literals.erase(lit); }
};

struct ClauseSet{
    std::vector<Clause> clauses;
    std::map<Proposition, bool> determined;
    ClauseSet(std::vector<Clause> clauses):clauses(clauses){ }
    void removeClausesWhichHas(const Literal& lit){
        clauses.erase(
            std::remove_if(clauses.begin(), clauses.end(), [&lit](const Clause& clause){
                return clause.has(lit);
            }), clauses.end());
    }
    void removeAll(const Literal& lit){
        for(Clause& clause : clauses)
            clause.remove(lit);
    }
    void determine(const Proposition& prop, bool value){
        determined[prop] = value;
    }
    bool isSatisfiable() {
        return clauses.empty();
    }
    bool isContradicted(){
        return std::any_of(clauses.begin(), clauses.end(), [](const Clause& clause){
            return clause.isContradicted();
        });
    }
    std::optional<Proposition> getOneProposition(){
        if(clauses.empty())
            return {};
        auto lit = clauses.begin()->literals;
        if(lit.empty())
            return {};
        return lit.begin()->prop;
    }
    std::optional<Literal> getPrimeLiteral(){
		for(auto&& clause : clauses)
			if(clause.isPrime())
				return *clause.literals.begin();
        return {};
    }
};
