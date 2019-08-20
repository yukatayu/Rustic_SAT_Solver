#pragma once
#include <vector>
#include <tuple>
#include "data.hpp"

std::tuple<bool, std::vector<ClauseSet>> solve(ClauseSet);

