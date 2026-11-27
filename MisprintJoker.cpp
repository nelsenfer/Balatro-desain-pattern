#include "MisprintJoker.h"

#include <cstdlib>

std::string MisprintJoker::getName() const {
    return "Misprint";
}

std::string MisprintJoker::getDescription(const ScoreContext&) const {
    return "+0-23 Mult (Random Mult)";
}

void MisprintJoker::onScoreCalculated(ScoreContext& context) {
    int bonus = std::rand() % 24; // 0 to 23
    context.mult += bonus;
}
