//
// Created by Henrik on 15-06-2024.
//

#include "build_sample_trejectory.h++"
#include "../Vessel.hpp"

/// Sample trajectory model.
Vessel sample_trajectory(uint32_t A, uint32_t B, uint32_t C)
{
    auto v = Vessel{"Sample trajectories of A, B and C"};
    const auto delay = 0.001; // reaction delay
    const auto agentA = v.add("A", A);
    const auto agentB = v.add("B", B);
    const auto agentC = v.add("C", C);
    v.add((agentA + agentC) >> delay >>= agentB + agentC);

    return v;
}
