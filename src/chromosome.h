#pragma once

#include "config.h"
#include <array>

using t_chromosome_data = std::array<std::size_t, N_QUEENS>;

struct t_chromosome {
    t_chromosome_data data;
    int fitness;
};
