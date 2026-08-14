#pragma once

namespace E::M {
static std::mt19937 rng(std::random_device{}());

float Random(float min, float max) {
    std::uniform_real_distribution distribution(min, max);
    return distribution(rng);
}

int Random(int min, int max) {
    std::uniform_int_distribution distribution(min, max);
    return distribution(rng);
}

float RandomGaussian(float mean, float standardDeviation) {
    std::normal_distribution distribution(mean, standardDeviation);
    return distribution(rng);
}
}
