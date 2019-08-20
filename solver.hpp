#pragma once
#include <vector>
#include <tuple>
#include "data.hpp"

std::tuple<bool, std::vector<std::map<Proposition, bool>>> solve(ClauseSet);
