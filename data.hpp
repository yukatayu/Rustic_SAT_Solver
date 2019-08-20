#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>

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

struct Clause {
    std::set<Literal> literals;
    bool has(const Literal& lit) const { return literals.count(lit); }
    bool isContradicted() const { return literals.empty(); }
    bool isPrime() const { return literals.size() == 1; }
    void remove(const Literal& lit){ literals.erase(lit); }
};

struct ClauseSet{
    std::vector<Clause> clauses;
    std::map<Proposition, bool> defined;
    ClauseSet(std::vector<Clause> clauses){
        this->clauses = clauses;
    }
    void removeWhichHas(const Literal& lit){
        clauses.erase(
            std::remove_if(clauses.begin(), clauses.end(), [&lit](const Clause& clause){
                return clause.has(lit);
            }), clauses.end());
    }
    void removeAll(const Literal& lit){
        for(Clause& clause : clauses){
            clause.remove(lit);
        }
    }
    void define(const Proposition& prop, bool value){
        defined[prop] = value;
    }
    bool isContradicted(){
        return std::any_of(clauses.begin(), clauses.end(), [](const Clause& clause){
            return clause.isContradicted();
        });
    }
};
